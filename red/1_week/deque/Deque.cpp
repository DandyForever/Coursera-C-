#include <vector>
#include <stdexcept>

template <typename T>
class Deque {
public:
    Deque () = default;
    bool Empty () const { return front_.empty() && back_.empty(); }
    size_t Size () const { return front_.size() + back_.size(); }
    T& operator[](size_t index) {
        if (front_.size() > index)
            return front_[front_.size() - index - 1];
        else
            return back_[index - front_.size()];
    }

    const T& operator[](size_t index) const {
        if (front_.size() > index)
            return front_[front_.size() - index - 1];
        else
            return back_[index - front_.size()];
    }

    T& At (size_t index) {
        if (index >= Size())
            throw std::out_of_range("bad index");
        return operator[](index);
    }

    const T& At(size_t index) const {
        if (index >= Size())
            throw std::out_of_range("bad index");
        return operator[](index);
    }

    T& Front() { return front_.empty() ? back_.front() : front_.back(); }
    const T& Front() const { return front_.empty() ? back_.front() : front_.back(); }
    T& Back() { return back_.empty() ? front_.front() : back_.back(); }
    const T& Back() const { return back_.empty() ? front_.front() : back_.back(); }
    void PushFront (const T& elem) { front_.push_back(elem); }
    void PushBack (const T& elem) { back_.push_back(elem); }

private:
    std::vector <T> front_;
    std::vector <T> back_;
};
