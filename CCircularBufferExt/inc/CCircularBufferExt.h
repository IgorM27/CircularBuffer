#pragma once

#include "CCircularBuffer.h"

template<typename T, typename Allocator = std::allocator<T>>
class CCircularBufferExt : public CCircularBuffer<T, Allocator> {
    using CCircularBuffer<T, Allocator>::CCircularBuffer;
public:
    using value_type = T;
    using reference = T&;
    using const_reference [[maybe_unused]] = const T&;
    using size_type = size_t;


    void push_front(const T& value) {
        if (this->size_ == this->capacity_) {
            if (this->capacity_ == 0) {
                this->resize(1);
            } else {
                this->resize(2 * this->capacity_);
            }
        }
        this->head_ = (this->head_ + this->capacity_ - 1) % this->capacity_;
        this->allocator_.construct(this->start_ + this->head_, value);
        this->size_++;
    }

    void push_back(const T& value) {
        if (this->size_ == this->capacity_) {
            if (this->capacity_ == 0) {
                this->resize(1);
            } else {
                this->resize(2 * this->capacity_);
            }
        }
        this->allocator_.construct(this->start_ + this->tail_, value);
        this->tail_ = (this->tail_ + 1) % this->capacity_;
        this->size_++;
    }

    CCircularBuffer_Iterator<T> insert(CCircularBuffer_Iterator<T> it, T value) {
        auto ans = this->begin();
        if (this->empty()) {
            return it;
        }
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i == it) {
                size_type counter = 0;
                CCircularBufferExt<T, std::allocator<T>> tmp(this->capacity_);
                for (auto j = this->begin(); j != it; j++, counter++) {
                    tmp.push_back(*j);
                }
                tmp.push_back(value);
                for (auto j = it; j != this->end(); j++) {
                    tmp.push_back(*j);
                }
                *this = tmp;
                return (this->begin() + counter);
            }
        }
        return it;
    }

    CCircularBuffer_Iterator<T> insert(CCircularBuffer_Iterator<T> it, size_type n, T value) {
        if (this->empty() || n == 0) {
            return it;
        }
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i == it) {
                size_type counter = 0;
                CCircularBufferExt<T, std::allocator<T>> tmp(this->capacity_);
                for (auto j = this->begin(); j != it; j++, counter++) {
                    tmp.push_back(*j);
                }
                for (size_type j = 0; j < n; ++j) {
                    tmp.push_back(value);
                }
                for (auto j = it; j != this->end(); j++) {
                    tmp.push_back(*j);
                }
                *this = tmp;
                return (this->begin() + counter);
            }
        }
        return it;
    }

    CCircularBuffer_Iterator<T> insert(CCircularBuffer_Iterator<T> it, std::initializer_list<value_type> list) {
        if (this->empty() || list.size() == 0) {
            return it;
        }
        for (auto i = this->begin(); i != this->end(); ++i) {
            if (i == it) {
                CCircularBufferExt<T, std::allocator<T>> tmp(this->capacity_);
                size_type counter = 0;
                for (auto j = this->begin(); j != it; j++, counter++) {
                    tmp.push_back(*j);
                }
                for (auto j = list.begin(); j != list.end(); j++) {
                    tmp.push_back(*j);
                }
                for (auto j = it; j != this->end(); j++) {
                    tmp.push_back(*j);
                }
                *this = tmp;
                return (this->begin() + counter);
            }
        }
        return it;
    }

};



