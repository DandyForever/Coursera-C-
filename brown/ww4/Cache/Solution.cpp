//#include "Common.h"
//#include <unordered_map>
//#include <mutex>
//
//using namespace std;
//
//class LruCache : public ICache {
//public:
//    LruCache(
//            shared_ptr<IBooksUnpacker> books_unpacker,
//            const Settings& settings
//    ): booksUnpacker(books_unpacker), settings_(settings){}
//
//    BookPtr GetBook(const string& book_name) override {
//        lock_guard g(m);
//        if (cache.count(book_name)) {
//            for (auto& [name, priority] : usage) {
//                priority--;
//            }
//            usage[book_name] = max_priority;
//            return cache[book_name];
//        }
//        auto book = BookPtr(booksUnpacker->UnpackBook(book_name));
//        if (book->GetContent().size() > settings_.max_memory) {
//            cache.clear();
//            usage.clear();
//            total_size = 0;
//            return std::move(book);
//        }
//        total_size += book->GetContent().size();
//        while (total_size > settings_.max_memory) {
//            int minimal_usage = max_priority;
//            string name_minimal;
//            for (auto& [name, use] : usage) {
//                if (use < minimal_usage) {
//                    minimal_usage = use;
//                    name_minimal = name;
//                }
//            }
//            total_size -= book->GetContent().size();
//            cache.erase(name_minimal);
//            usage.erase(name_minimal);
//        }
//        cache[book_name] = std::move(book);
//        for (auto& [name, priority] : usage) {
//            priority--;
//        }
//        usage[book_name] = max_priority;
//        return cache[book_name];
////        if (book->GetContent().size() <= settings_.max_memory) {
////            while (book->GetContent().size() + total_size > settings_.max_memory) {
////                int minimal_usage = max_priority;
////                string name_minimal;
////                for (auto& [name, use] : usage) {
////                    if (use < minimal_usage) {
////                        minimal_usage = use;
////                        name_minimal = name;
////                    }
////                }
////                total_size -= book->GetContent().size();
////                cache.erase(name_minimal);
////                usage.erase(name_minimal);
////            }
////            cache[book_name] = book;
////            for (auto& [name, priority] : usage) {
////                priority--;
////            }
////            usage[book_name] = max_priority;
////            total_size += book->GetContent().size();
////        } else {
////            cache.clear();
////            usage.clear();
////            total_size = 0;
////            return std::move(book);
////        }
////        return book;
//    }
//
//private:
//    unordered_map<string, BookPtr> cache;
//    unordered_map<string, int> usage;
//    const int max_priority = 1000000;
//    int total_size = 0;
//    shared_ptr<IBooksUnpacker> booksUnpacker;
//    const Settings& settings_;
//    mutex m;
//};
//
//
//unique_ptr<ICache> MakeCache(
//        shared_ptr<IBooksUnpacker> books_unpacker,
//        const ICache::Settings& settings
//) {
//    return make_unique<LruCache>(books_unpacker, settings);
//}
#include "Common.h"

#include <unordered_map>
#include <list>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
            shared_ptr<IBooksUnpacker> books_unpacker, const Settings &settings) :
            books_unpacker_(move(books_unpacker)), settings_(settings) {}

    BookPtr GetBook(const string &book_name) override {
        lock_guard<mutex> lock(mx);

        if (auto it = cache_.find(book_name); it != cache_.end()) {
            rate_.splice(rate_.begin(), rate_, it->second);
            return rate_.front();
        }

        auto book = books_unpacker_->UnpackBook(book_name);

        if (book->GetContent().size() > settings_.max_memory) {
            rate_.clear();
            cache_.clear();
            total_size = 0;

            return move(book);
        }

        total_size += book->GetContent().size();

        while (total_size > settings_.max_memory) {
            total_size -= rate_.back()->GetContent().size();
            cache_.erase(rate_.back()->GetName());
            rate_.pop_back();
        }

        rate_.emplace_front(move(book));
        cache_[rate_.front()->GetName()] = rate_.begin();

        return *cache_[book_name];
    }

private:
    shared_ptr<IBooksUnpacker> books_unpacker_;
    const Settings settings_;
    list<BookPtr> rate_;
    unordered_map<string, list<BookPtr>::iterator> cache_;
    size_t total_size = 0;
    mutex mx;
};


unique_ptr<ICache> MakeCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const ICache::Settings &settings
) {
    return make_unique<LruCache>(books_unpacker, settings);
}