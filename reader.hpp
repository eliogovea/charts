#pragma once

class reader {
public:
    virtual int read() = 0;
    virtual int min_value() const = 0;
    virtual int max_value() const = 0;
};
 
class analog_reader : public reader {
public:
    analog_reader(int pin) : pin_(pin), reader() {}
    int read() override {
        return analogRead(pin_);
    }
    int min_value() const override {
    	return 0;
    }
    int max_value() const override {
    	return 1 << 10;
    }
private:
    int pin_;
};

// for testing
class mock_reader : public reader {
public:
    mock_reader(int min_value, int max_value) : min_value_(min_value), max_value_(max_value), reader() {}
    int read() override {
        int value = 0.5 * (min_value_ + max_value_) + 0.5 * sin(0.1 * step_) * (max_value_ - min_value_);
        step_++;
        return value;
    }
    int min_value() const override {
      return min_value_;
    }
    int max_value() const override {
      return max_value_;
    }
private:
    int step_{0};
    int min_value_;
    int max_value_;
};
