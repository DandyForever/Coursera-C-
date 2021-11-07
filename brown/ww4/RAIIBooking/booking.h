#pragma once

namespace RAII {
template<typename Provider>
class Booking {
public:
    Booking(Provider *pr, int counter) : provider_(pr), counter_(counter) {}

    Booking(const Booking<Provider> &) = delete;

    Booking(Booking<Provider> &&other) : provider_(other.provider_) {
        other.provider_ = nullptr;
    }

    Booking<Provider> &operator=(Booking<Provider> &) = delete;

    Booking<Provider> &operator=(Booking<Provider> &&other) {
        delete provider_;
        provider_ = other.provider_;
        other.provider_ = nullptr;
        return *this;
    }

    ~Booking() {
        if (provider_) {
            provider_->CancelOrComplete(*this);
        }
    }

    Provider *provider_;
    int counter_;
};
}