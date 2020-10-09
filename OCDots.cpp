//
// Created by Gustavo Batistela on 09/10/2020.
//

#include "OCDots.h"
#include <exception>

OCDots::OCDots(double viscosity) {
    if (viscosity < 0.) std::terminate();
    m_viscosity = viscosity;
}


double OCDots::Viscosity() const {
    return m_viscosity;
}

void OCDots::SetViscosity(double viscosity) {
    if (viscosity < 0.) std::terminate();
    m_viscosity = viscosity;
}
