//
// Created by Gustavo Batistela on 09/10/2020.
//
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#ifndef OCDOTS_H
#define OCDOTS_H


class Vector {
public:
    float x, y;
    std::string name;
    Vector(float x, float y, std::string name = "vector") {
        this->x = x;
        this->y = y;
        this->name = name;
    }
    Vector clone(void) { return Vector(this->x, this->y, this->name); };
    std::string to_string(void) {
        return name + " - x: " + std::to_string(this->x) + ", y: " + std::to_string(this->y);
    }
    float norm2(void) {
        return std::pow(this->x, 2) + std::pow(this->y, 2);
    };
    float norm(void) {
        return std::sqrt(this->norm2());
    };
    float dot(Vector g) { return this->x * g.x + this->y * g.y; };
    Vector operator+(float F) { return Vector(this->x + F, this->y + F, this->name); };
    Vector operator-(float F) { return Vector(this->x - F, this->y - F, this->name); };
    Vector operator*(float F) { return Vector(this->x * F, this->y * F, this->name); };
    Vector operator/(float F) { return Vector(this->x / F, this->y / F, this->name); };
    Vector operator+=(float F) {
        *this = *this + F;
        return *this;
    };
    Vector operator-=(float F) {
        *this = *this - F;
        return *this;
    };
    Vector operator*=(float F) {
        *this = *this * F;
        return *this;
    };
    Vector operator/=(float F) {
        *this = *this / F;
        return *this;
    };
    friend Vector operator+(float F, Vector g) { return Vector(F + g.x, F + g.y, g.name); };
    friend Vector operator-(float F, Vector g) { return Vector(F - g.x, F - g.y, g.name); };
    friend Vector operator*(float F, Vector g) { return Vector(F * g.x, F * g.y, g.name); };
    friend Vector operator/(float F, Vector g) { return Vector(F / g.x, F / g.y, g.name); };

    Vector operator+(Vector g) { return Vector(this->x + g.x, this->y + g.y, this->name); };
    Vector operator-(Vector g) { return Vector(this->x - g.x, this->y - g.y, this->name); };
    Vector operator-(void) { return Vector(-this->x, -this->y, this->name); };
    Vector operator+=(Vector g) {
        *this = *this + g;
        return *this;
    };
    Vector operator-=(Vector g) {
        *this = *this - g;
        return *this;
    };
};

class Dot {
public:
    Vector p = Vector(0, 0, "position"), m = Vector(0, 0, "momentum");
    Dot(Vector p) {
        this->p = p;
    }
    Dot(Vector p, Vector m) {
        this->p = p;
        this->m = m;
    }
    Dot(float x, float y) {
        this->p.x = x;
        this->p.y = y;
    }
    Dot(float x, float y, float mx, float my) {
        this->p.x = x;
        this->p.y = y;
        this->m.x = mx;
        this->m.y = my;
    }
    Vector distanceTo(Dot d) {
        return d.p - this->p;
    }
    Vector distanceTo(Vector v) {
        return v - this->p;
    }
    Dot clone(void) { return Dot(this->p, this->m); };
    std::string to_string(void) {
        return "Dot - " + this->p.to_string() + " " + this->m.to_string();
    }
};


class OCDots {
public:
    ~OCDots() = default;
    std::vector<Dot> movePoints(
            std::vector<Dot> dots,
            std::vector<Vector> polygon,
            float baseForce = 2,
            float drag = 0.05,
            float viscosity = 0.1,
            float maxMomentum = 5);
    Vector pointForces(Dot d, std::vector<Dot>);
    Vector polygonForces(Dot d, std::vector<Vector>);
    Vector perpendicularToLine(Vector p, Vector v0, Vector v1);
    bool checkInbounds(Dot d, std::vector<Vector> polygon);
};


#endif//OCPPDOTS_OCDOTS_H
