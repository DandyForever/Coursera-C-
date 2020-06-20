#include <map>
#include <queue>
#include <set>
#include <iostream>
using namespace std;

struct Reservation {
    long long time;
    string hotel;
    int client_id;
    int room_count;
};

class BookingManager {
public:
    int clientsNumber (const string& hotel) const {
        if (user_booking_count_.count(hotel))
            return user_booking_count_.at(hotel).size();
        return 0;
    }
    int roomsNumber (const string& hotel) const {
        if (rooms_booked_.count(hotel))
            return rooms_booked_.at(hotel);
        return 0;
    }
    void addReservation (const Reservation& book) {
        fresh_reservations_.push(book);
        rooms_booked_[book.hotel] += book.room_count;
        user_booking_count_[book.hotel][book.client_id].insert(book.time);
        update (book);
    }
private:
    queue<Reservation> fresh_reservations_;
    map<string, int> rooms_booked_;
    map<string, map<int, set<int>>> user_booking_count_;

    void update (const Reservation& book) {
        long long threshold = book.time - 86400;
        Reservation& rmv = fresh_reservations_.front();
        while (rmv.time <= threshold) {
            fresh_reservations_.pop();
            rooms_booked_[rmv.hotel] -= rmv.room_count;
            user_booking_count_[rmv.hotel][rmv.client_id].erase(rmv.time);
            if (user_booking_count_[rmv.hotel][rmv.client_id].empty())
                user_booking_count_[rmv.hotel].erase(rmv.client_id);
            rmv = fresh_reservations_.front();
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int requests = 0;
    cin >> requests;

    BookingManager manager;
    for (int request_id = 0; request_id < requests; request_id++) {
        string request_type;
        cin >> request_type;
        if (request_type == "CLIENTS") {
            string hotel;
            cin >> hotel;
            cout << manager.clientsNumber(hotel) << '\n';
        } else if (request_type == "ROOMS") {
            string hotel;
            cin >> hotel;
            cout << manager.roomsNumber(hotel) << '\n';
        } else if (request_type == "BOOK") {
            long long time = 0;
            int client_id = 0, room_count = 0;
            string hotel;
            cin >> time >> hotel >> client_id >> room_count;
            manager.addReservation ({time, hotel, client_id, room_count});
        }
    }
    return 0;
}