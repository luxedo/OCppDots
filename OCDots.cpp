//
// Created by Gustavo Batistela on 09/10/2020.
//
#include "OCDots.h"
#include <exception>

#define BASE_FORCE 2

std::vector<Dot> OCDots::movePoints(std::vector<Dot> dots, std::vector<Vector> polygon) {
    int N = dots.size();
    int S = 120;// TODO: calculate perimeter of polygon
    std::vector<Dot> dots_final;

    // Calculate forces
    for (Dot d : dots) {
        Force pf = OCDots::pointForces(d, dots);                // Point forces
        Force bf = OCDots::polygonForces(d, polygon);           // Boundary forces
        Force f = pow(10, BASE_FORCE) * (pf + (2 * N * bf) / S);// Final Force
        dots_final.push_back(OCDots::updateMomentum(d, f));     // Update momentum
    }

    // Move points
    for (int i = 0; i < N; i++) {
        Dot d = dots_final[i].clone();
        d.x += d.mx;
        d.y += d.my;
        if (!OCDots::checkInbounds(d, polygon)) {
            // If dot would end up out of bounds then zero it's momentum
            // and don't move the dot in this iteration
            dots_final[i].mx = 0;
            dots_final[i].my = 0;
        } else {
            // Update dot position
            dots_final[i] = d;
        }
    }
    return dots_final;
}

Force OCDots::pointForces(Dot d, std::vector<Dot> dots) {
    Force f = Force(0, 0);
    for (Dot e : dots) {
        Vector r = d.distanceTo(e);
        float norm = r.norm();
        float norm3 = pow(norm == 0 ? INFINITY : norm, 3);
        f += Force(-r.x / norm3, -r.y / norm3);
    }
    return f;
}

Force OCDots::polygonForces(Dot d, std::vector<Vector> polygon) {
    // TODO
    return {0.0, 0.0};
}

Dot OCDots::updateMomentum(Dot d, Force f) {
    Dot e = d.clone();
    e.mx += f.x;
    e.my += f.y;
    // TODO Add drag
    // TODO Add viscosity
    return e;
}

bool OCDots::checkInbounds(Dot d, std::vector<Vector> polygon) {
    // TODO
    return true;
}

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
