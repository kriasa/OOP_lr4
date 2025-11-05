#pragma once
#include "point.h"
#include <memory>
#include <vector>
#include <stdexcept>
#include <typeinfo> 
#include <cmath>

template <Number T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point<T> getCenter() const = 0;
    virtual double area() const = 0;
    virtual std::vector<std::unique_ptr<Point<T>>> getVertices() const = 0;
    virtual void print(std::ostream& os) const = 0;
    
    virtual operator double() const {
        return area();
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    virtual bool operator==(const Figure<T>& other) const {
        if (typeid(*this) != typeid(other)) {
            return false;
        }

        auto vertices1 = this->getVertices();
        auto vertices2 = other.getVertices();
        
        if (vertices1.size() != vertices2.size()) return false;
        
        for (size_t i = 0; i < vertices1.size(); ++i) {
            if (!vertices1[i] || !vertices2[i] || (*vertices1[i] != *vertices2[i])) return false;
        }
        
        return true;
    }
    
    virtual bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }
};