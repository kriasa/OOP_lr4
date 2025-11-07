
#pragma once

#include "figure.h"
#include <memory>
#include <vector>
#include <stdexcept>

template <Number T>

class Rhombus : public Figure<T> {

private:
    std::unique_ptr<Point<T>> center;
    T horizontal_diagonal;
    T vertical_diagonal;
    
public:
    Rhombus()
    : center(std::make_unique<Point<T>>(Point<T>(0,0))),
      horizontal_diagonal(1),
      vertical_diagonal(1) {}


    Rhombus(const Point<T>& _center, T h_diag, T v_diag) 
        : center(std::make_unique<Point<T>>(_center)), 
          horizontal_diagonal(h_diag), 
          vertical_diagonal(v_diag) {
              if (h_diag <= 0 || v_diag <= 0){ 
                throw std::invalid_argument("Diagonals must be positive.");
              }
          }

    Rhombus(const Rhombus& other)
        : center(std::make_unique<Point<T>>(*other.center)),
          horizontal_diagonal(other.horizontal_diagonal),
          vertical_diagonal(other.vertical_diagonal) {}

    Rhombus& operator=(const Rhombus& other) {

        if (this != &other) {
            center = std::make_unique<Point<T>>(*other.center);
            horizontal_diagonal = other.horizontal_diagonal;
            vertical_diagonal = other.vertical_diagonal;
        }
        return *this;
    }
    
    Rhombus& operator=(Rhombus&& other) noexcept {

        if (this != &other) {
            center = std::move(other.center);
            horizontal_diagonal = other.horizontal_diagonal;
            vertical_diagonal = other.vertical_diagonal;
            other.horizontal_diagonal = 0;
            other.vertical_diagonal = 0;
        }
        return *this;
    }

    Point<T> getCenter() const override { return *center; }
    double area() const override { return (horizontal_diagonal * vertical_diagonal) / 2.0; }

    std::vector<std::unique_ptr<Point<T>>> getVertices() const override {
        std::vector<std::unique_ptr<Point<T>>> vertices;
        T half_h = horizontal_diagonal / 2;
        T half_v = vertical_diagonal / 2;
        
        vertices.push_back(std::make_unique<Point<T>>(center->getX(), center->getY() + half_v));
        vertices.push_back(std::make_unique<Point<T>>(center->getX() + half_h, center->getY()));
        vertices.push_back(std::make_unique<Point<T>>(center->getX(), center->getY() - half_v));
        vertices.push_back(std::make_unique<Point<T>>(center->getX() - half_h, center->getY()));
            
        return vertices;
    }

    void print(std::ostream& os) const override {
        auto vertices = getVertices();
        os << "Rhombus (d1=" << horizontal_diagonal << ", d2=" << vertical_diagonal << ")";
        for (size_t i = 0; i < vertices.size(); i++) {
            os << *vertices[i];
            if (i< vertices.size()-1){
                os<<", ";
            }
        }
        os << "Area: " << area() << " Center: " << getCenter();
    }
};