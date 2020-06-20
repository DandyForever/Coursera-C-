#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <utility>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size){
        begin_ = new T[size];
        end_ = begin_ + size;
        capacity_ = size;
    }
    ~SimpleVector() {
        if (capacity_ == 1) delete begin_;
        else if (capacity_) delete[] begin_;
        begin_ = nullptr;
        end_ = nullptr;
        capacity_ = 0;
    }

    T& operator[](size_t index) { return begin_[index]; }

    T* begin() { return begin_; }
    T* end() { return end_; }
    const T* begin() const { return begin_; }
    const T* end() const { return end_; }

    size_t Size() const { return capacity_ == 0 ? 0 : end_ - begin_; }
    size_t Capacity() const { return capacity_; }
    void PushBack(T value){
        if (!capacity_) {
            begin_ = new T(std::move(value));
            end_ = begin_ + 1;
            capacity_ = 1;
            return;
        } else if (capacity_ == Size())
            Resize();
        *end_ = std::move(value);
        end_++;
    }

private:
    T* begin_ = nullptr;
    T* end_ = nullptr;
    size_t capacity_ = 0;

    void Resize () {
        T* temp = new T[capacity_ * 2];
        std::move (begin_, end_, temp);
        end_ = temp + Size();
        if (capacity_ == 1) delete begin_;
        else delete[] begin_;
        begin_ = temp;
        capacity_ = capacity_ * 2;
    }
};