#include <string>
#include <utility>

using namespace std;

class INotifier {
public:
    virtual void Notify (const string& message) = 0;
};

class SmsNotifier : public INotifier {
public:
    explicit SmsNotifier (string  phoneNumber) :
    phoneNumber_(phoneNumber) {}
    void Notify (const string& message) override {
        SendSms(phoneNumber_, message);
    }
private:
    string phoneNumber_;
};

class EmailNotifier : public INotifier {
public:
    explicit EmailNotifier (string emailAddress) :
    emailAddress_(emailAddress) {}
    void Notify (const string& message) override {
        SendEmail(emailAddress_, message);
    }
private:
    string emailAddress_;
};