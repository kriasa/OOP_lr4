#pragma once
#include "figure.h"
#include <memory>
#include <vector>
#include <cmath>
#include <stdexcept>

template <Number T>
class Hexagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> center;
    T radius;
public:
    Hexagon()
    : center(std::make_unique<Point<T>>(Point<T>(0,0))),
      radius(1) {}

    Hexagon(const Point<T>& _center, T _radius) 
        : center(std::make_unique<Point<T>>(_center)), radius(_radius) {
            if (_radius <= 0) throw std::invalid_argument("Radius must be positive.");
        }

    Hexagon(const Hexagon& other)
        : center(std::make_unique<Point<T>>(*other.center)),
          radius(other.radius) {}

    Hexagon& operator=(const Hexagon& other) {
        if (this != &other) {
            center = std::make_unique<Point<T>>(*other.center);
            radius = other.radius;
        }
        return *this;
    }
    
    Hexagon& operator=(Hexagon&& other) noexcept {
        if (this != &other) {
            center = std::move(other.center);
            radius = other.radius;
            other.radius = 0;
        }
        return *this;
    }

    Point<T> getCenter() const override { return *center; }
    double area() const override {
        return (3.0 * std::sqrt(3.0) * radius * radius) / 2.0;
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        const int N = 6;
        
        for (int i = 0; i < N; ++i) {
            double angle = 2.0 * M_PI * i / N - M_PI / 6.0; 
            T x = center->getX() + radius * std::cos(angle);
            T y = center->getY() + radius * std::sin(angle);
            vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
        
        return vertices;
    }

    void print(std::ostream& os) const override {
        auto vertices = getVertices();
        os << "Hexagon (R=" << radius << ") [";
        for (size_t i = 0; i < vertices.size(); ++i) {
            os << *vertices[i] << (i < vertices.size() - 1 ? ", " : "");
        }
        os << " ] Area: " << area() << " Center: " << getCenter();
    }
};