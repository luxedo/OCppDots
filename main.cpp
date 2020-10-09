#include <iostream>
#include "OCDots.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    
    OCDots dots(3.8);
    std::cout << "Viscosity: " << dots.Viscosity() << '\n';
    
    return 0;
}
