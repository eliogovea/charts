#pragma once

const int max_points = 40;

class buffer {
public:
    buffer() {
        top_ = 0;
        for (int i = 0; i < max_points; i++) {
            values_[i] = 0;
        }
    }
    int size() const {
        return max_points;
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
        if (top_ >= max_points) {
            top_ = 0;
        }
    }
private:
    int top_;
    int values_[max_points];
};

class reader {
public:
    virtual int read() = 0;
    virtual int min_value() = 0;
    virtual int max_value() = 0;
    const buffer& get_buffer() {
        return buffer_;
    }
    buffer buffer_{};
};

class mock_reader : public reader {
public:
    mock_reader() : reader() {}
    int read() override {
        int value = (1 << 9) + 0.5 * sin(0.1 * step_) * (max_value() - min_value());
        step_++;
        buffer_.push(value);
        return value;
    }
    int min_value() override {
        return 0;
    }
    int max_value() override {
        return 1 << 10;
    }
public:
    int step_{0};
};
 
class analog_reader : public reader {
public:
    analog_reader(int pin) : pin_(pin), reader() {}
    int read() override {
        int value = analogRead(pin_);
        buffer_.push(value);
        return value;
    }
    int min_value() override {
        return 0;
    }
    int max_value() override {
        return 1 << 10;
    }
private:
    int pin_;
};
