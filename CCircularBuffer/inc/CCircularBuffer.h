#pragma once

#include <stdexcept>
#include <memory>
#include <iostream>
#include "CCircularBuffer_Iterator.h"
#include "CCircularBuffer_ConstIterator.h"

template<typename T, typename Allocator = std::allocator<T>>
class CCircularBuffer {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

protected:
    T* start_ = nullptr;
    size_type capacity_;
    size_type size_ = 0;
    size_type head_ = 0;
    size_type tail_ = 0;
    Allocator allocator_;
public:

    CCircularBuffer() {
        capacity_ = 0;
        CCircularBuffer(0);
    }

    explicit CCircularBuffer(size_type capacity, const Allocator& allocator = Allocator()) {
        allocator_ = allocator;
        start_ = allocator_.allocate(capacity);
        capacity_ = capacity;
    }

    CCircularBuffer(const CCircularBuffer& other) {
        allocator_ = other.allocator_;
        start_ = allocator_.allocate(other.capacity_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        head_ = other.head_;
        tail_ = other.tail_;
        if (size_ != 0) {
            size_type i = 0;
            do {
                allocator_.construct(start_ + head_, other[i]);
                head_ = (head_ + 1) % capacity_;
                i++;
            } while (head_ != tail_);
            head_ = other.head_;
        }
    }

    friend bool operator==(CCircularBuffer& lhs, CCircularBuffer& rhs) {
        if (lhs.size_ != rhs.size_ || lhs.capacity_ != rhs.capacity_) {
            return false;
        }
        auto tmp1 = lhs.begin();
        auto tmp2 = rhs.begin();
        for (; tmp1 != lhs.end(); ++tmp1, ++tmp2) {
            if (*tmp1 != *tmp2) {
                return false;
            }
        }
        return true;
    };

    friend bool operator!=(CCircularBuffer& lhs, CCircularBuffer& rhs) {
        return !(lhs == rhs);
    }

    CCircularBuffer& operator=(CCircularBuffer other) {
        if (*this != other) {
            clear();
            allocator_ = other.allocator_;
            if (capacity_ != other.capacity_) {
                allocator_.deallocate(start_, capacity_);
                start_ = allocator_.allocate(other.capacity_);
                capacity_ = other.capacity_;
            }
            size_ = other.size_;
            head_ = other.head_;
            tail_ = other.tail_;
            if (size_ != 0) {
                size_type i = 0;
                do {
                    allocator_.construct(start_ + head_, other[i]);
                    head_ = (head_ + 1) % capacity_;
                    i++;
                } while (head_ != tail_);
                head_ = other.head_;
            }
        }
        return *this;
    }

    ~CCircularBuffer() {
        clear();
        allocator_.deallocate(start_, capacity_);
    }


    reference operator[](size_type ind) {
        if (ind >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return start_[(head_ + ind) % capacity_];
    }

    reference operator[](size_type ind) const {
        if (ind >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return start_[(head_ + ind) % capacity_];
    }

    [[maybe_unused]] reference front() {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        return start_[head_];
    }

    [[maybe_unused]] [[nodiscard]] const_reference c_front() const {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        return start_[head_];
    }

    [[maybe_unused]] reference back() {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        return start_[(tail_ - 1 + capacity_) % capacity_];
    }

    [[maybe_unused]] [[nodiscard]] const_reference c_back() const {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        return start_[(tail_ - 1 + capacity_) % capacity_];
    }

    virtual void push_back(const T& value) {
        if (size_ == capacity_) {
            pop_front();
        }
        allocator_.construct(start_ + tail_, value);
        tail_ = (tail_ + 1) % capacity_;
        size_++;
    }

    void clear() {
        while (size_ > 0) {
            pop_front();
        }
    }

    void pop_front() {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        allocator_.destroy(start_ + head_);
        head_ = (head_ + 1) % capacity_;
        --size_;
    }

    [[maybe_unused]] [[nodiscard]] size_type size() const {
        return size_;
    }

    [[maybe_unused]] [[nodiscard]] size_type capacity() const {
        return capacity_;
    }

    [[nodiscard]] bool empty() const {
        return size_ == 0;
    }

    CCircularBuffer_Iterator<T> begin() {
        return CCircularBuffer_Iterator<T>(start_, 0, head_, tail_, size_, capacity_, true, false);
    }

    [[maybe_unused]] [[nodiscard]] CCircularBuffer_ConstIterator<T> cbegin() const {
        return CCircularBuffer_ConstIterator<T>(start_, 0, head_, tail_, size_, capacity_, true, false);
    }

    CCircularBuffer_Iterator<T> end() {
        return CCircularBuffer_Iterator<T>(start_, size_, head_, tail_, size_, capacity_, false, true);
    }

    [[maybe_unused]] [[nodiscard]] CCircularBuffer_ConstIterator<T> cend() const {
        return CCircularBuffer_ConstIterator<T>(start_, size_, head_, tail_, size_, capacity_, false, true);
    }

    CCircularBuffer_Iterator<T> erase(CCircularBuffer_Iterator<T> it) {
        CCircularBuffer<T, std::allocator<T>> tmp1(capacity_);
        CCircularBuffer_Iterator<T> tmp2 = this->end();
        for (auto a = this->begin(); a != this->end(); a++) {
            if (a != it) {
                tmp1.push_back(*a);
            } else {
                tmp2 = a;
            }
        }
        *this = tmp1;
        return tmp2;
    }

    CCircularBuffer_Iterator<T> erase(CCircularBuffer_Iterator<T> it1, CCircularBuffer_Iterator<T> it2) {
        CCircularBuffer<T, std::allocator<T>> tmp1(capacity_);
        CCircularBuffer_Iterator<T> tmp2 = this->end();
        if (it2 <= it1) {
            return it2;
        }
        for (auto a = this->begin(); a != this->end(); a++) {
            if (a >= it1 && a < it2) {
                tmp2 = it2;
            } else {
                tmp1.push_back(*a);
            }
        }
        *this = tmp1;
        return tmp2;
    }

    virtual CCircularBuffer_Iterator<T> insert(CCircularBuffer_Iterator<T> it, T value) {
        auto ans = this->begin();
        if (this->empty()) {
            return it;
        }
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i == it) {
                size_type counter = 0;
                CCircularBuffer<T, std::allocator<T>> tmp(capacity_);
                for (auto j = this->begin(); j != it; j++, counter++) {
                    tmp.push_back(*j);
                }
                int delta1 = counter;
                tmp.push_back(value);
                counter++;
                size_type delta2 = 0;
                int del = counter - capacity_;
                if (del > 0) {
                    delta2 = del % capacity_;
                }
                for (auto j = it; j != this->end() && counter < capacity_; j++, counter++) {
                    tmp.push_back(*j);
                }
                *this = tmp;
                return (this->begin() + delta1 - delta2);
            }
        }
        return it;
    }


    virtual CCircularBuffer_Iterator<T> insert(CCircularBuffer_Iterator<T> it, size_type n, T value) {
        if (this->empty() || n == 0) {
            return it;
        }
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i == it) {
                size_type counter = 0;
                CCircularBuffer<T, std::allocator<T>> tmp(capacity_);
                for (auto j = this->begin(); j != it; j++, counter++) {
                    tmp.push_back(*j);
                }
                size_type delta1 = counter;
                for (size_type j = 0; j < n; ++j, counter++) {
                    tmp.push_back(value);
                }
                size_type delta2 = 0;
                int del = counter - capacity_;
                if (del > 0) {
                    delta2 = del % capacity_;
                }
                for (auto j = it; j != this->end() && counter < capacity_; j++, counter++) {
                    tmp.push_back(*j);
                }
                *this = tmp;
                return (this->begin() + delta1 - delta2);
            }
        }
        return it;
    }

    virtual CCircularBuffer_Iterator<T> insert(CCircularBuffer_Iterator<T> it, std::initializer_list<value_type> list) {
        if (this->empty() || list.size() == 0) {
            return it;
        }
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i == it) {
                CCircularBuffer<T, std::allocator<T>> tmp(capacity_);
                size_type counter = 0;
                for (auto j = this->begin(); j != it; j++, counter++) {
                    tmp.push_back(*j);
                }
                size_type delta1 = counter;
                for (auto j = list.begin(); j != list.end(); j++, counter++) {
                    tmp.push_back(*j);
                }
                size_type delta2 = 0;
                int del = counter - capacity_;
                if (del > 0) {
                    delta2 = del % capacity_;
                }
                for (auto j = it; j != this->end() && counter < capacity_; j++, counter++) {
                    tmp.push_back(*j);
                }
                *this = tmp;
                return (this->begin() + delta1 - delta2);
            }
        }
        return it;
    }

    void pop_before() {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        allocator_.destroy(start_ + (head_ + capacity_ - 1) % capacity_);
        tail_ = (tail_ + capacity_ - 1) % capacity_;
        --size_;
    }

    virtual void push_front(const T& value) {
        if (size_ == capacity_) {
            pop_before();
        }
        head_ = (head_ + capacity_ - 1) % capacity_;
        allocator_.construct(start_ + head_, value);
        size_++;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Empty buffer");
        }
        allocator_.destroy(start_ + tail_);
        tail_ = (tail_ + capacity_ - 1) % capacity_;
        --size_;
    }

    void resize(size_type n) {
        size_ = n;
        while (capacity_ < size_) {
            if (capacity_ == 0) {
                reserve(1);
            } else {
                reserve(capacity_ * 2);
            }
        }
    }

    void reserve(size_type n) {
        CCircularBuffer<T, std::allocator<T>> tmp(n);
        size_type counter = 0;
        for (auto i = this->begin(); i != this->end() && counter < n; ++i, ++counter) {
            tmp.push_back(*i);
        }
        *this = tmp;
    }

    void asign(size_type n, T value) {
        CCircularBuffer<T, std::allocator<T>> tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp.push_back(value);
        }
        *this = tmp;
    }

    void asign(CCircularBuffer_Iterator<T> it1, CCircularBuffer_Iterator<T> it2) {
        size_type counter = 0;
        for (CCircularBuffer_Iterator<T> i = it1; i != it2; ++i) {
            counter++;
        }
        CCircularBuffer<T, std::allocator<T>> tmp(counter);
        for (CCircularBuffer_Iterator<T> i = it1; i != it2; ++i) {
            tmp.push_back(*i);
        }
        *this = tmp;
    }

    void asign(std::initializer_list<value_type> list) {
        size_type counter = 0;
        for (auto i = list.begin(); i != list.end(); ++i) {
            counter++;
        }
        CCircularBuffer<T, std::allocator<T>> tmp(counter);
        for (auto i = list.begin(); i != list.end(); ++i) {
            tmp.push_back(*i);
        }
        *this = tmp;
    }

    void swap(CCircularBuffer& other) {
        CCircularBuffer<T, std::allocator<T>> tmp = *this;
        *this = other;
        other = tmp;
    }

};
