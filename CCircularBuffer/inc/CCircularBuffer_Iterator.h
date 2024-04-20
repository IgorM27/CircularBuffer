#pragma once

#include <stdexcept>
#include <memory>
#include <iostream>

template<typename T>
class CCircularBuffer_Iterator {
public:
    using value_type = T;
    using iterator_category [[maybe_unused]] = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using size_type = std::size_t;

private:
    pointer start;
    size_type head = 0;
    size_type tail = 0;
    int pos_ = 0;
    size_type size = 0;
    size_type capacity = 0;
    bool beg = false;
    bool end = false;
public:

    CCircularBuffer_Iterator() = default;;

    CCircularBuffer_Iterator(pointer start, int pos, size_type head, size_type tail, size_type size, size_type capacity,
                             bool beg_, bool end_) {
        this->start = start;
        pos_ = pos;
        this->head = head;
        this->tail = tail;
        this->size = size;
        this->capacity = capacity;
        beg = beg_;
        end = end_;
    }

    pointer operator->() {
        return *(start[(pos_ + head + (std::abs(pos_) / capacity + 1) * capacity) % capacity]);
    }

    reference operator*() {
        return start[(pos_ + head + (std::abs(pos_) / capacity + 1) * capacity) % capacity];
    }

    reference operator[](difference_type value) {
        return start[(pos_ + head + value + (std::abs(value + pos_) + 1) * capacity) % capacity];
    }


    CCircularBuffer_Iterator& operator--() {
        beg = false;
        pos_--;
        return *this;
    }

    CCircularBuffer_Iterator& operator--(int) {
        return --(*this);
    }

    CCircularBuffer_Iterator& operator++() {
        beg = false;
        pos_++;
        return *this;
    }

    CCircularBuffer_Iterator& operator++(int) {
        return ++(*this);;
    }


    CCircularBuffer_Iterator operator+(difference_type value) {
        CCircularBuffer_Iterator<T> ans = *this;
        ans.beg = false;
        ans.pos_ = this->pos_ + value;
        return ans;
    }

    CCircularBuffer_Iterator operator-(difference_type value) {
        CCircularBuffer_Iterator<T> ans = *this;
        ans.beg = false;
        ans.pos_ = this->pos_ - value;
        return ans;
    }

    CCircularBuffer_Iterator& operator+=(difference_type value) {
        beg = false;
        pos_ = pos_ + value;
        return *this;
    }


    CCircularBuffer_Iterator& operator-=(difference_type value) {
        beg = false;
        pos_ = pos_ - value;
        return *this;
    }

    friend bool operator==(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        if (lhs.capacity == 0 || rhs.capacity == 0) {
            if (lhs.capacity == rhs.capacity) {
                return true;
            }
            return false;
        }
        return ((lhs.pos_ + lhs.head + (std::abs(lhs.pos_) / lhs.capacity + 1) * lhs.capacity) % lhs.capacity ==
                (rhs.pos_ + rhs.head + (std::abs(rhs.pos_) / rhs.capacity + 1) * rhs.capacity) % rhs.capacity &&
                !(lhs.beg && rhs.end) || (lhs.size == 0 && rhs.size == 0));
    }

    friend bool operator!=(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return (lhs.pos_ + lhs.head + (std::abs(lhs.pos_) / lhs.capacity + 1) * lhs.capacity) % lhs.capacity <
               (rhs.pos_ + rhs.head + (std::abs(rhs.pos_) / rhs.capacity + 1) * rhs.capacity) % rhs.capacity;
    }

    friend bool operator<=(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return (lhs < rhs || lhs == rhs);
    }

    friend bool operator>(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return (lhs.pos_ + lhs.head + (std::abs(lhs.pos_) / lhs.capacity + 1) * lhs.capacity) % lhs.capacity >
               (rhs.pos_ + rhs.head + (std::abs(rhs.pos_) / rhs.capacity + 1) * rhs.capacity) % rhs.capacity;
    }

    friend bool operator>=(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return (lhs > rhs || lhs == rhs);
    }

    friend CCircularBuffer_Iterator operator+(difference_type value, const CCircularBuffer_Iterator<T>& tmp1) {
        CCircularBuffer_Iterator<T> tmp2 = tmp1;
        tmp2 += value;
        return tmp2;
    }

    friend CCircularBuffer_Iterator operator-(difference_type value, const CCircularBuffer_Iterator& tmp1) {
        CCircularBuffer_Iterator<T> tmp2 = tmp1;
        tmp2 -= value;
        return tmp2;
    }

    friend difference_type operator+(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return static_cast<difference_type>(lhs.pos_ + rhs.pos_);
    }

    friend difference_type operator-(const CCircularBuffer_Iterator& lhs, const CCircularBuffer_Iterator& rhs) {
        return static_cast<difference_type>(lhs.pos_ - rhs.pos_);
    }
};

