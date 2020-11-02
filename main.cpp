#include "OCDots.h"
#include <iostream>

int main() {
    OCDots ds{};

    std::vector<Dot> dots = {
            Dot(10, 13, 0, 0),
            Dot(20, 23, 0, 0),
            Dot(10, 23, 0, 0),
            Dot(20, 13, 0, 0),
            Dot(20, 14, 0, 0),
            Dot(21, 14, 0, 0),
            Dot(22, 14, 0, 0),
    };
    std::vector<Vector> polygon = {
            Vector(0, 0),
            Vector(0, 30),
            Vector(30, 30),
            Vector(30, 0),
            Vector(0, 0)};
    std::cout << "Dots before:" << std::endl;
    for (Dot d : dots)
        std::cout << d.to_string() << std::endl;

    for (int i = 0; i < 1001; i++) {
        dots = ds.movePoints(dots, polygon);
        if (i % 100 == 0) {
            std::cout << "Dots iter: " << std::to_string(i) << std::endl;
            for (Dot d : dots)
                std::cout << d.to_string() << std::endl;
        }
    }
    return 0;
}
