#ifndef VEC2_HPP
#define VEC2_HPP

namespace ge::physics2d {

struct Vec2 {
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    ~Vec2() = default;

    float Magnitude() const;
    Vec2& Normalize();

    Vec2& operator=(const Vec2& v);       // v1 = v2
    bool operator==(const Vec2& v) const; // v1 == v2
    bool operator!=(const Vec2& v) const; // v1 != v2

    Vec2 operator+(const Vec2& v) const; // v1 + v2
    Vec2 operator-(const Vec2& v) const; // v1 - v2
    Vec2 operator*(const float n) const; // v1 * n
    Vec2 operator/(const float n) const; // v1 / n
};
} // namespace ge::physics2d

#endif