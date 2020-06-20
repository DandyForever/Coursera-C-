#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>

template <typename T>
class SimpleVector {
public:
    SimpleVector()
        :begin_(nullptr),
        end_(nullptr),
        capacity_(0) {}
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
    void PushBack(const T& value){
        if (!capacity_) {
            begin_ = new T(value);
            end_ = begin_ + 1;
            capacity_ = 1;
            return;
        } else if (capacity_ == Size())
            Resize();
        *end_ = value;
        end_++;
    }

    SimpleVector& operator= (const SimpleVector& other) {
        delete[] begin_;
        begin_ = new T[other.Size()];
        std::copy(other.begin(), other.end(), begin_);
        end_ = begin_ + other.Size();
        capacity_ = other.Size();
        return *this;
    }

private:
    T* begin_;
    T* end_;
    size_t capacity_;

    void Resize () {
        T* temp = new T[capacity_ * 2];
        std::copy (begin_, end_, temp);
        end_ = temp + Size();
        if (capacity_ == 1) delete begin_;
        else delete[] begin_;
        begin_ = temp;
        capacity_ = capacity_ * 2;
    }
};