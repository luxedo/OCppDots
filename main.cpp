#include "OCDots.h"
#include <iostream>

int main() {
    OCDots ds(3.8);
    int N = 4;
    std::vector<Dot> dots = {
            Dot(10, 10),
            Dot(10, 20),
            Dot(20, 20),
            Dot(20, 10)};

    std::vector<Vector> polygon = {
            Vector(0, 0),
            Vector(0, 30),
            Vector(30, 30),
            Vector(30, 0)};
    std::cout << "Dots before:" << std::endl;
    for (Dot d : dots)
        std::cout << d.to_string() << std::endl;
    std::vector<Dot> dots_final = ds.movePoints(dots, polygon);
    std::cout << "Dots after:" << std::endl;
    for (Dot d : dots_final)
        std::cout << d.to_string() << std::endl;

    return 0;
}
