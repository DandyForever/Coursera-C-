#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // С‚РѕР»СЊРєРѕ РїРµСЂРІРѕРјСѓ worker-Сѓ РІ РїР°Р№РїР»Р°Р№РЅРµ РЅСѓР¶РЅРѕ СЌС‚Рѕ РёРјРїР»РµРјРµРЅС‚РёСЂРѕРІР°С‚СЊ
    throw logic_error("Unimplemented");
  }

protected:
  // СЂРµР°Р»РёР·Р°С†РёРё РґРѕР»Р¶РЅС‹ РІС‹Р·С‹РІР°С‚СЊ PassOn, С‡С‚РѕР±С‹ РїРµСЂРµРґР°С‚СЊ РѕР±СЉРµРєС‚ РґР°Р»СЊС€Рµ
  // РїРѕ С†РµРїРѕС‡РєРµ РѕР±СЂР°Р±РѕС‚С‡РёРєРѕРІ
  void PassOn(unique_ptr<Email> email) const {
      if (next_) {
          next_->Process(std::move(email));
      }
  }

public:
  void SetNext(unique_ptr<Worker> next) {
      next_ = std::move(next);
  }

private:
    unique_ptr<Worker> next_;
};


class Reader : public Worker {
public:
    Reader(istream& is): input(is) {}
    void Run() override {
        while (true) {
            auto email = make_unique<Email>();
            if (!getline(input, email->from))
                break;
            getline(input, email->to);
            getline(input, email->body);
            PassOn(std::move(email));
        }
    }
    void Process(unique_ptr<Email> email) override {};

private:
    istream& input;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

  Filter(Function pred): predicate(pred) {}
  void Process(unique_ptr<Email> email) override {
      if (predicate(*email)) {
          PassOn(std::move(email));
      }
  }

private:
    Function predicate;
};


class Copier : public Worker {
public:
  Copier(string recipient): recipient(recipient) {}
  void Process(unique_ptr<Email> email) override {
      if (email->to != recipient) {
          auto duplicate = make_unique<Email>();
          duplicate->from = email->from;
          duplicate->to = recipient;
          duplicate->body = email->body;
          PassOn(std::move(email));
          PassOn(std::move(duplicate));
          return;
      }
      PassOn(std::move(email));
  }

private:
    string recipient;
};


class Sender : public Worker {
public:
  Sender(ostream& os): output(os) {}
  void Process(unique_ptr<Email> email) override {
      output << email->from << "\n" << email->to << "\n" << email->body << "\n";
      PassOn(std::move(email));
  }

private:
    ostream& output;
};


// СЂРµР°Р»РёР·СѓР№С‚Рµ РєР»Р°СЃСЃ
class PipelineBuilder {
public:
  // РґРѕР±Р°РІР»СЏРµС‚ РІ РєР°С‡РµСЃС‚РІРµ РїРµСЂРІРѕРіРѕ РѕР±СЂР°Р±РѕС‚С‡РёРєР° Reader
  explicit PipelineBuilder(istream& in): worker(make_unique<Reader>(in)) {
      workers.push_back(worker.get());
  }

  // РґРѕР±Р°РІР»СЏРµС‚ РЅРѕРІС‹Р№ РѕР±СЂР°Р±РѕС‚С‡РёРє Filter
  PipelineBuilder& FilterBy(Filter::Function filter) {
      unique_ptr<Worker> filter_ = make_unique<Filter>(filter);
      Worker* filter_pointer = filter_.get();
      workers.back()->SetNext(std::move(filter_));
      workers.push_back(filter_pointer);
      return *this;
  }

  // РґРѕР±Р°РІР»СЏРµС‚ РЅРѕРІС‹Р№ РѕР±СЂР°Р±РѕС‚С‡РёРє Copier
  PipelineBuilder& CopyTo(string recipient) {
      unique_ptr<Worker> copier_ = make_unique<Copier>(recipient);
      Worker* copier_pointer = copier_.get();
      workers.back()->SetNext(std::move(copier_));
      workers.push_back(copier_pointer);
      return *this;
  }

  // РґРѕР±Р°РІР»СЏРµС‚ РЅРѕРІС‹Р№ РѕР±СЂР°Р±РѕС‚С‡РёРє Sender
  PipelineBuilder& Send(ostream& out) {
      unique_ptr<Worker> sender_ = make_unique<Sender>(out);
      Worker* sender_pointer = sender_.get();
      workers.back()->SetNext(std::move(sender_));
      workers.push_back(sender_pointer);
      return *this;
  }

  // РІРѕР·РІСЂР°С‰Р°РµС‚ РіРѕС‚РѕРІСѓСЋ С†РµРїРѕС‡РєСѓ РѕР±СЂР°Р±РѕС‚С‡РёРєРѕРІ
  unique_ptr<Worker> Build() {
      return std::move(worker);
  }

private:
    unique_ptr<Worker> worker;
    std::vector<Worker*> workers;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}