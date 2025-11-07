
#pragma once

#include "figure.h"
#include <memory>
#include <vector>
#include <cmath>
#include <stdexcept>

template <Number T>

class Pentagon : public Figure<T> {

private:
    std::unique_ptr<Point<T>> center;
    T radius;

public:
    Pentagon()
    : center(std::make_unique<Point<T>>(Point<T>(0,0))),
      radius(1) {}

    Pentagon(const Point<T>& _center, T _radius) 
        : center(std::make_unique<Point<T>>(_center)), radius(_radius) {
            if (_radius <= 0){ 
                throw std::invalid_argument("Radius must be positive");
            }
        }

    Pentagon(const Pentagon& other)
        : center(std::make_unique<Point<T>>(*other.center)),
          radius(other.radius) {}

    Pentagon& operator=(const Pentagon& other) {
        
        if (this != &other) {
            center = std::make_unique<Point<T>>(*other.center);
            radius = other.radius;
        }
        return *this;
    }
    
    Pentagon& operator=(Pentagon&& other) noexcept {

        if (this != &other) {
            center = std::move(other.center);
            radius = other.radius;
            other.radius = 0;
        }
        return *this;
    }

    Point<T> getCenter() const override { return *center; }
    double area() const override {
        return (5.0 * radius * radius * std::sin(2.0 * M_PI / 5.0)) / 2.0;
    }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;

        const int N = 5;
        
        for (int i = 0; i < N; i++) {
            double angle = 2.0 * M_PI * i / N - M_PI / 2.0; 
            T x = center->getX() + radius * std::cos(angle);
            T y = center->getY() + radius * std::sin(angle);
            vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
        
        return vertices;
    }

    void print(std::ostream& os) const override {

        auto vertices = getVertices();
        os << "Pentagon (R=" << radius << ")";

        for (size_t i = 0; i < vertices.size(); i++) {
            os << *vertices[i];
            if (i< vertices.size()-1){
                os<<" ";
            }
        }
        os << "Area:" << area() << "Center:" << getCenter();
    }
};