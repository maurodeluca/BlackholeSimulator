#pragma once
#include <cmath>
#include "Constants.hpp"

struct Vec2f {
    float x, y;
    Vec2f() : x(0), y(0) {}
    Vec2f(float x, float y) : x(x), y(y) {}

    Vec2f operator+(const Vec2f& v) const { return Vec2f(x + v.x, y + v.y); }
    Vec2f operator-(const Vec2f& v) const { return Vec2f(x - v.x, y - v.y); }
    Vec2f operator*(float s) const { return Vec2f(x * s, y * s); }
    float length() const { return std::sqrt(x * x + y * y); }
    Vec2f normalized() const {
        float len = length();
        return (len > 0) ? (*this) * (1.f / len) : Vec2f();
    }

    static bool isInFront(sf::Vector2f const& p) {
        float dx = p.x - BLACKHOLE_CENTER.x;
        float dy = p.y - BLACKHOLE_CENTER.y;
        return (dx * dx + dy * dy) < (BLACKHOLE_RADIUS * BLACKHOLE_RADIUS);
        // true if inside the circle → **in front**
    };
};
