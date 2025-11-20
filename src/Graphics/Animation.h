#pragma once
#include <string>

struct Animation {
    std::string name;
    int row;
    int frameCount;
    int speed;

    Animation(std::string n = "", int r = 0, int f = 0, int s = 0) 
        : name(n), row(r), frameCount(f), speed(s) {}
};
