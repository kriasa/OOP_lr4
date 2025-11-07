
#pragma once

#include <concepts>
#include <iostream>
#include <memory>
#include <cmath>
#include <type_traits>
#include <limits>
#include <algorithm>

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type 
nearlyEqual(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 10) {
    return std::abs(a - b) <= epsilon * std::max({std::abs(a), std::abs(b), (T)1.0});
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type 
nearlyEqual(T a, T b) {
    return a == b;
}

template <typename T>

concept Number = std::is_default_constructible<T>::value && 
                (std::integral<T> || std::floating_point<T>);

template <Number T>

class Point {
    friend std::ostream &operator<<(std::ostream &os, const Point<T> &rhv) {
        os << "(" << rhv.x << " " << rhv.y << ")";
        return os;
    }

    friend bool operator==(const Point<T>& lhs, const Point<T>& rhs) {
        return nearlyEqual(lhs.x, rhs.x) && nearlyEqual(lhs.y, rhs.y);
    }

    friend bool operator!=(const Point<T>& lhs, const Point<T>& rhs) {
        return !(lhs == rhs);
    }

private:
    T x;
    T y;

public:
    Point() : x(0), y(0) {}
    Point(const T& _x, const T& _y) : x(_x), y(_y) {}

    T getX() const { return x; }
    T getY() const { return y; }
    void setX(const T& _x) { x = _x; }
    void setY(const T& _y) { y = _y; }

    double distanceTo(const Point<T>& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};