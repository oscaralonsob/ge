#include "Vec2.hpp"

#include <math.h>

namespace ge::physics2d {

Vec2::Vec2() : x(0.0), y(0.0) {
}

Vec2::Vec2(float x, float y) : x(x), y(y) {
}

float Vec2::Magnitude() const {
    return sqrtf(x * x + y * y);
}

Vec2& Vec2::Normalize() {
    float length = Magnitude();
    if (length != 0.0) {
        x = x / length;
        y = y / length;
    }
    return *this;
}

Vec2& Vec2::operator=(const Vec2& v) {
    x = v.x;
    y = v.y;
    return *this;
}

bool Vec2::operator==(const Vec2& v) const {
    return x == v.x && y == v.y;
}

bool Vec2::operator!=(const Vec2& v) const {
    return x != v.x || y != v.y;
}

Vec2 Vec2::operator+(const Vec2& v) const {
    Vec2 result;
    result.x = x + v.x;
    result.y = y + v.y;
    return result;
}

Vec2 Vec2::operator-(const Vec2& v) const {
    Vec2 result;
    result.x = x - v.x;
    result.y = y - v.y;
    return result;
}

Vec2 Vec2::operator*(const float n) const {
    Vec2 result;
    result.x = x * n;
    result.y = y * n;
    return result;
}

Vec2 Vec2::operator/(const float n) const {
    Vec2 result;
    result.x = x / n;
    result.y = y / n;
    return result;
}

} // namespace ge::physics2d