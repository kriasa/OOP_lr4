#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>
#include <limits>
#include "point.h"
#include "figure.h"
#include "rhombus.h"
#include "pentagon.h"
#include "hexagon.h"
#include "array.h"

void printMenu() {
    std::cout << "1. Add figure" << std::endl;
    std::cout << "2. Print all figures" << std::endl;
    std::cout << "3. Calculate total area" << std::endl;
    std::cout << "4. Delete figure by index" << std::endl;
    std::cout << "5. Clear screen" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose option:";
}

void addFigureMenu(Array<std::shared_ptr<Figure<double>>>& figures) {
    std::cout << "\nADD FIGURE" << std::endl;
    std::cout << "Choose figure type:" << std::endl;
    std::cout << "1. Rhombus" << std::endl;
    std::cout << "2. Pentagon" << std::endl;
    std::cout << "3. Hexagon" << std::endl;
    std::cout << "0. Back to main menu" << std::endl;
    std::cout << "Choose type:";
    
    int typeChoice;
    if (!(std::cin >> typeChoice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Please enter a number." << std::endl;
        return;
    }
    
    if (typeChoice == 0) return;
    
    double centerX, centerY;
    std::cout << "Enter center coordinates (x y):";
    if (!(std::cin >> centerX >> centerY)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid coordinates!" << std::endl;
        return;
    }
    Point<double> center(centerX, centerY);
    
    try {
        switch (typeChoice) {
            case 1: {
                double d1, d2;
                std::cout << "d1 d2 : ";
                if (!(std::cin >> d1 >> d2)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid diagonals!" << std::endl;
                    return;
                }
                figures.push_back(std::make_shared<Rhombus<double>>(center, d1, d2));
                std::cout << "Rhombus added successfully!" << std::endl;
                break;
            }
            case 2: {
                double radius;
                std::cout << "Enter radius: ";
                if (!(std::cin >> radius)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid radius!" << std::endl;
                    return;
                }
                figures.push_back(std::make_shared<Pentagon<double>>(center, radius));
                std::cout << "Pentagon added successfully!" << std::endl;
                break;
            }
            case 3: {
                double radius;
                std::cout << "Enter radius:";
                if (!(std::cin >> radius)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid radius!" << std::endl;
                    return;
                }
                figures.push_back(std::make_shared<Hexagon<double>>(center, radius));
                std::cout << "Hexagon added successfully!" << std::endl;
                break;
            }
            default:
                std::cout << "Invalid figure type!" << std::endl;
                return;
        }
    } catch (const std::exception& e) {
        std::cout << "Error creating figure:" << e.what() << std::endl;
    }
}

void printAllFigures(Array<std::shared_ptr<Figure<double>>>& figures) {
    std::cout << "\nALL FIGURES (" << figures.size() << " total)" << std::endl;
    
    if (figures.size() == 0) {
        std::cout << "No figures in array." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i << ": ";
        figures[i]->print(std::cout);
        std::cout << std::endl;
        std::cout << "  Center: " << figures[i]->getCenter() << std::endl;
        std::cout << "  Area: " << figures[i]->area() << std::endl;
        std::cout << std::endl;
    }
}

void deleteFigureMenu(Array<std::shared_ptr<Figure<double>>>& figures) {
    std::cout << "\nDELETE FIGURE" << std::endl;
    
    if (figures.size() == 0) {
        std::cout << "No figures to delete." << std::endl;
        return;
    }
    
    std::cout << "Current figures (0 to " << figures.size() - 1 << "):" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << i << ": ";
        figures[i]->print(std::cout);
        std::cout << std::endl;
    }
    
    std::cout << "Enter index to delete:";
    size_t index;
    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    
    if (index < figures.size()) {
        figures.erase(index);
        std::cout << "Figure at index " << index << " deleted successfully!" << std::endl;
    } else {
        std::cout << "Invalid index!" << std::endl;
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    int choice;
    do {
        printMenu();
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number (0-5)." << std::endl;
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        try {
            switch (choice) {
                case 1:
                    addFigureMenu(figures);
                    break;
                case 2:
                    printAllFigures(figures);
                    break;
                case 3:
                    std::cout << "\nTOTAL AREA" << std::endl;
                    if (figures.size() == 0) {
                        std::cout << "No figures in array." << std::endl;
                    } else {
                        std::cout << "Total area of all " << figures.size() 
                                  << " figures: " << figures.totalArea() << std::endl;
                    }
                    break;
                case 4:
                    deleteFigureMenu(figures);
                    break;
                case 5:
                    clearScreen();
                    break;
                case 0:
                    std::cout << "\nEXITING" << std::endl;
                    std::cout << "Final array size:" << figures.size() << std::endl;
                    std::cout << "Final total area:" << figures.totalArea() << std::endl;
                    break;
                default:
                    std::cout << "Invalid option! Please enter a number between 0 and 5." << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << "Error:" << e.what() << std::endl;
        }
        
    } while (choice != 0);

    return 0;
}