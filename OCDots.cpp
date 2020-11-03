//
// Created by Gustavo Batistela on 09/10/2020.
//
#include "OCDots.h"

std::vector<Dot> OCDots::movePoints(
        std::vector<Dot> dots,
        std::vector<Vector> polygon,
        float baseForce,
        float drag,
        float viscosity,
        float maxMomentum) {
    const int N = dots.size();
    std::vector<Dot> dots_final;
    int S = 0;
    for (unsigned int i = 1; i < polygon.size(); i++)
        S += (polygon[i] - polygon[i - 1]).norm();

    for (Dot d : dots) {
        // Calculate forces
        Vector pf = OCDots::pointForces(d, dots);                   // Point forces
        Vector bf = OCDots::polygonForces(d, polygon);              // Boundary forces
        Vector force = pow(10, baseForce) * (pf + (2 * N * bf) / S);// Final force Vector

        // Update momentum
        Dot e = d;
        e.m += force;
        const float norm2 = e.m.norm2();
        if (norm2 != 0) {
            // TODO: Think better about this logic
            const float norm = std::sqrt(norm2);
            float modulo = norm - drag * norm2;// Momentum minus drag
            modulo = modulo < 0 ? 0.1 : (modulo > maxMomentum ? maxMomentum : modulo);
            modulo = modulo < viscosity ? 0 : modulo;
            e.m = Vector(modulo * e.m.x / norm, modulo * e.m.y / norm, e.m.name);
        }
        dots_final.push_back(e);
    }

    // Move points
    for (int i = 0; i < N; i++) {
        Dot d = dots_final[i];
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
        const float norm = r.norm();
        const float norm3 = std::pow(norm == 0 ? INFINITY : norm, 3);
        force += Vector(-r.x / norm3, -r.y / norm3);
    }
    return -force;
}

Vector OCDots::polygonForces(Dot d, std::vector<Vector> polygon) {
    // https://aapt.scitation.org/doi/full/10.1119/1.4906421
    const int N = polygon.size();
    Vector force = Vector(0, 0, "polygonForce");
    for (int i = 1; i < N; i++) {
        Vector v0 = polygon[i - 1];
        Vector v1 = polygon[i];

        Vector t = OCDots::perpendicularToLine(d.p, v0, v1);
        Vector p = Vector(-t.y, t.x);
        const float nt = t.norm();

        Vector v0p = d.p - v0;
        Vector v1p = d.p - v1;
        const float thetaA = std::atan2(v0p.y, v0p.x) - std::atan2(t.y, t.x);
        const float thetaB = std::atan2(v1p.y, v1p.x) - std::atan2(t.y, t.x);
        float dTheta = thetaB - thetaA;
        dTheta = dTheta <= -M_PI ? dTheta + 2 * M_PI : dTheta;
        dTheta = dTheta > M_PI ? dTheta - 2 * M_PI : dTheta;

        const float modulo = (1.0 / nt) * std::sin(dTheta / 2.0);

        const float tv = std::sin(thetaB) - std::sin(thetaA);
        const float pv = -(std::cos(thetaB) - std::cos(thetaA));

        Vector f = (tv * t) + (pv * p);
        f *= modulo / f.norm();
        force += f;
    }
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
    // https://en.wikipedia.org/wiki/Even%E2%80%93odd_rule
    // https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
    // TODO Vectorize maybe? Not so CHUCHU
    unsigned int j = polygon.size() - 1;
    bool c = false;
    for (unsigned int i = 0; i < polygon.size(); i++) {
        if ((polygon[i].y > d.p.y) != (polygon[j].y > d.p.y) &&
            (d.p.x < polygon[i].x +
                             (polygon[j].x - polygon[i].x) *
                                     (d.p.y - polygon[i].y) /
                                     (polygon[j].y - polygon[i].y))) c = !c;
        j = i;
    }
    return c;
}
