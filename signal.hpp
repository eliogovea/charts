#pragma once

#include "reader.hpp"

class buffer {
public:
    buffer(int size_ = max_points) : size_(size_) {
        if (size_ > max_points) {
            size_ = max_points;
            // TODO report
        }
        top_ = 0;
        for (int i = 0; i < size_; i++) {
            values_[i] = 0;
        }
    }
    const int size() const {
        return size_;
    }
    const int& at(int idx) const {
        idx += top_;
        if (idx >= max_points) {
          idx -= max_points;
        }
        return values_[idx];
    }
    void push(int value) {
        values_[top_] = value;
        top_++;
        if (top_ >= size_) {
            top_ = 0;
        }
    }
private:
    static const int max_points{40};
    int top_;
    int size_;
    int values_[max_points];
};

class signal {
public:
    signal(reader& r) : reader_(r) {}
    void read() {
        auto value = reader_.read();
        buffer_.push(value);
    }
    const buffer& get_buffer() const {
        return buffer_;
    }
    const reader& get_reader() const {
    	return reader_;
    }
private:
    reader& reader_;
    int min_value_;
    int max_value_;
    buffer buffer_{};
};
