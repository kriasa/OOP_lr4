#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>
#include "point.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"
#include "array.h"

template<Number T>
void demonstrateFigure(const std::string& name, const Figure<T>& fig) {
    std::cout << "=== " << name << " ===" << std::endl;
    std::cout << fig << std::endl;
    std::cout << "Geometric Center: " << fig.getCenter() << std::endl;
    std::cout << "Area (via double conversion): " << static_cast<double>(fig) << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Laboratory Work: MetaProgramming with Figures ===" << std::endl;
    
    Array<std::shared_ptr<Figure<double>>> figureArray;

    try {
        std::cout << "\n1. DEMONSTRATING DIFFERENT SCALAR TYPES" << std::endl;
        
        Rhombus<double> rhombus_double(Point<double>(0.0, 0.0), 4.5, 6.5);
        demonstrateFigure("Rhombus (double)", rhombus_double);

        Pentagon<int> pentagon_int(Point<int>(1, 1), 5);
        demonstrateFigure("Pentagon (int)", pentagon_int);

        Hexagon<float> hexagon_float(Point<float>(2.5f, 2.5f), 3.5f);
        demonstrateFigure("Hexagon (float)", hexagon_float);

        std::cout << "\n2. DEMONSTRATING ARRAY WITH shared_ptr<Figure<double>>" << std::endl;
        
        figureArray.push_back(std::make_shared<Rhombus<double>>(Point<double>(0, 0), 4.0, 6.0));
        figureArray.push_back(std::make_shared<Pentagon<double>>(Point<double>(2, 2), 3.0));
        figureArray.push_back(std::make_shared<Hexagon<double>>(Point<double>(4, 4), 2.5));
        
        std::cout << "Array contains " << figureArray.size() << " figures:" << std::endl;
        for (size_t i = 0; i < figureArray.size(); ++i) { 
            std::cout << "Figure " << i << ": ";
            figureArray[i]->print(std::cout);
            std::cout << std::endl;
        }
        
        std::cout << "Total area of all figures: " << figureArray.totalArea() << std::endl;
        std::cout << "\n3. DEMONSTRATING REMOVAL" << std::endl;
        std::cout << "Removing figure at index 1..." << std::endl;
        figureArray.erase(1);
        std::cout << "Now array contains " << figureArray.size() << " figures" << std::endl;
        std::cout << "Total area after removal: " << figureArray.totalArea() << std::endl;
        std::cout << "\n4. DEMONSTRATING TEMPLATE ARRAY WITH SPECIFIC TYPES" << std::endl;

        Array<Rhombus<int>> rhombusArray;
        rhombusArray.push_back(Rhombus<int>(Point<int>(0, 0), 4, 6));
        rhombusArray.push_back(Rhombus<int>(Point<int>(5, 5), 3, 4));
        rhombusArray.push_back(Rhombus<int>(Point<int>(1, 1), 7, 2));
        
        std::cout << "Rhombus array size: " << rhombusArray.size() << std::endl;
        std::cout << "Total area of rhombus array: " << rhombusArray.totalArea() << std::endl;

        std::cout << "\n5. DEMONSTRATING STANDARD INPUT" << std::endl;
        double d1, d2;
        Point<double> input_center(10.0, 10.0);
        std::cout << "Enter two diagonal values for a new Rhombus<double> (d1 d2): ";
        
        if (std::cin >> d1 >> d2) {
            figureArray.push_back(
                std::make_shared<Rhombus<double>>(input_center, d1, d2)
            );
            std::cout << "Rhombus<double> added. New Array Size: " << figureArray.size() << std::endl;
            std::cout << "Total area after input: " << figureArray.totalArea() << std::endl;
        } else {
            std::cerr << "Invalid input." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n=== Laboratory Work Completed ===" << std::endl;
    return 0;
}