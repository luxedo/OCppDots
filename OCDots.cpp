//
// Created by Gustavo Batistela on 09/10/2020.
//
#include "OCDots.h"
#include <exception>


std::vector<Dot> OCDots::movePoints(std::vector<Dot> dots, std::vector<Vector> polygon) {
    static int N = dots.size();
    static int S = 120;// TODO: calculate perimeter of polygon
    static float baseForce = 2;
    static float drag = 0.05;
    static float maxMomentum = 5;
    std::vector<Dot> dots_final;

    for (Dot d : dots) {
        // Calculate forces
        Vector pf = OCDots::pointForces(d, dots);                   // Point forces
        Vector bf = OCDots::polygonForces(d, polygon);              // Boundary forces
        Vector force = pow(10, baseForce) * (pf + (2 * N * bf) / S);// Final force Vector

        // Update momentum
        Dot e = d.clone();
        e.m += force;
        float norm2 = e.m.norm();
        if (!norm2 == 0) {
            float norm = std::sqrt(norm2);
            float modulo = norm - drag * norm2;// Momentum minus drag
            modulo = modulo < 0 ? 0.1 : (modulo > maxMomentum ? maxMomentum : modulo);
            // TODO Add viscosity
            e.m = Vector(modulo * e.m.x / norm, modulo * e.m.y / norm, e.m.name);
        }
        dots_final.push_back(e);
    }

    // Move points
    for (int i = 0; i < N; i++) {
        Dot d = dots_final[i].clone();
        d.p += d.m;
        if (!OCDots::checkInbounds(d, polygon)) {
            // If dot would end up out of bounds then zero it's momentum
            // and don't move the dot in this iteration
            dots_final[i].m.x = 0;
            dots_final[i].m.y = 0;
        } else {
            // Update dot position
            dots_final[i] = d;
        }
    }
    return dots_final;
}

Vector OCDots::pointForces(Dot d, std::vector<Dot> dots) {
    Vector force = Vector(0, 0, "pointForce");
    for (Dot e : dots) {
        Vector r = d.p - e.p;
        float norm = r.norm();
        float norm3 = std::pow(norm == 0 ? INFINITY : norm, 3);
        force += Vector(-r.x / norm3, -r.y / norm3);
    }
    return force;
}

Vector OCDots::polygonForces(Dot d, std::vector<Vector> polygon) {
    // https://aapt.scitation.org/doi/full/10.1119/1.4906421
    static int N = polygon.size();
    Vector force = Vector(0, 0, "polygonForce");
    for (int i = 1; i < N; i++) {
        Vector v0 = polygon[i - 1];
        Vector v1 = polygon[i];

        Vector t = OCDots::perpendicularToLine(d.p, v0, v1);
        Vector p = Vector(-t.y, t.x);
        float nt = t.norm();

        Vector v0p = d.p - v0;
        Vector v1p = d.p - v1;
        float thetaA = std::atan2(v0p.y, v0p.x) - std::atan2(t.y, t.x);
        float thetaB = std::atan2(v1p.y, v1p.x) - std::atan2(t.y, t.x);
        float dTheta = thetaB - thetaA;
        dTheta = dTheta <= -M_PI ? dTheta + 2 * M_PI : dTheta;
        dTheta = dTheta > M_PI ? dTheta - 2 * M_PI : dTheta;

        float modulo = (1.0 / nt) * std::sin(dTheta / 2.0);

        float tv = std::sin(thetaB) - std::sin(thetaA);
        float pv = -(std::cos(thetaB) - std::cos(thetaA));

        Vector f = (tv * t) + (pv * p);
        f *= modulo / f.norm();
        // std::cout << "d: " << d.p.to_string() << std::endl;
        // std::cout << v0.to_string() << std::endl;
        // std::cout << v1.to_string() << std::endl;
        // std::cout << "t: " << t.to_string() << std::endl;
        // std::cout << "p: " << p.to_string() << std::endl;
        // std::cout << "f: " << f.to_string() << std::endl;
        // std::cout << "tv:" << std::to_string(tv) << std::endl;
        // std::cout << "pv:" << std::to_string(pv) << std::endl;
        // std::cout << "f_norm:" << std::to_string(f.norm()) << std::endl;
        // std::cout << "modulo:" << std::to_string(modulo) << std::endl;
        // std::cout << "thetaA:" << std::to_string(thetaA) << std::endl;
        // std::cout << "thetaB:" << std::to_string(thetaB) << std::endl;
        // std::cout << "dTheta:" << std::to_string(dTheta) << std::endl;
        // std::cout << "v0p: " << v0p.to_string() << std::endl;
        // std::cout << "v1p: " << v1p.to_string() << std::endl;
        // std::cout << std::endl;
        force += f;
    }
    // std::cout << force.to_string() << std::endl;
    return force;
}

Vector OCDots::perpendicularToLine(Vector p, Vector v0, Vector v1) {
    // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Vector_formulation
    Vector n = v0 - v1;
    n = n / n.norm();
    Vector v0p = v0 - p;
    return v0p - (v0p.dot(n) * n);// UM CHUCHU! 😘
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
