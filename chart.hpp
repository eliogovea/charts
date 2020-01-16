#pragma once

#include <UTFT.h>

#include "signal.hpp"

class chart {
public:
    chart(UTFT& display);
    void draw_axis(int r, int g, int b);
    void draw_signal(const signal& data, int r, int g, int b);
    void remove_signal(const signal& s);
private:
    UTFT& display_;
    
    int width_         {300};
    int height_        {220};
    int bottom_left_x_ {10};
    int bottom_left_y_ {10};
    int margin_        {5};

    int background_r{0};
    int background_g{0};
    int background_b{0};
};

int fit(int min_o, int max_o, int value, int min_, int max_) {
    return min_ + (float)(value - min_o) / (float)(max_o - min_o) * (float)(max_ - min_);
}

int flip(int min_, int max_, int value) {
    return min_ + max_ - value;
}

chart::chart(UTFT& display) : display_(display) {}

void chart::draw_axis(int r, int g, int b) {
    int origin_x = bottom_left_x_ + margin_;
    int origin_y = bottom_left_y_ + margin_;
    
    display_.setColor(r, g, b);
    display_.drawLine(bottom_left_x_, bottom_left_y_ + margin_, bottom_left_x_ + width_, bottom_left_y_ + margin_);
    display_.drawLine(flip(bottom_left_x_, bottom_left_x_ + width_, bottom_left_x_ + margin_), bottom_left_y_,
                     flip(bottom_left_x_, bottom_left_x_ + width_, bottom_left_x_ + margin_), bottom_left_y_ + height_);

    // TODO axis arrows
}


void chart::draw_signal(const signal& s, int r, int g, int b) {
    int size = s.get_buffer().size();
    if (size < 2) {
        return;
    }
    display_.setColor(r, g, b);
    auto get_x = [&](int idx) {
        int x = fit(0, size - 1, idx, bottom_left_x_ + margin_, bottom_left_x_ + width_ - margin_);
        return flip(bottom_left_x_ + margin_, bottom_left_x_ + width_ - margin_, x);
    };
    auto get_y = [&](int y) {
        return fit(s.get_reader().min_value(), s.get_reader().max_value(), y, bottom_left_y_ + margin_, bottom_left_y_ + height_ - margin_);
    };
    int last_x = get_x(0);
    int last_y = get_y(s.get_buffer().at(0));
    for (int i = 1; i < size; i++) {
        int cur_x = get_x(i);
        int cur_y = get_y(s.get_buffer().at(i));
        display_.drawLine(last_x, last_y, cur_x, cur_y);
        last_x = cur_x;
        last_y = cur_y;
    }
}

void chart::remove_signal(const signal& s) { // signal buffer did not change since the last draw_signal !!!
    draw_signal(s, background_r, background_g, background_b);
}
