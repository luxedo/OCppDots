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
    Vector(float x, float y) {
        this->x = x;
        this->y = y;
    }
    Vector clone(void) { return Vector(this->x, this->y); };
    std::string to_string(void) {
        return "x: " + std::to_string(this->x) + ", y: " + std::to_string(this->y);
    }
    float norm(void) {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    };
    float dot(Vector g) { return this->x * g.x + this->y * g.y; };
    Vector operator+(int I) { return Vector(this->x + I, this->y + I); };
    Vector operator-(int I) { return Vector(this->x - I, this->y - I); };
    Vector operator*(int I) { return Vector(this->x * I, this->y * I); };
    Vector operator/(int I) { return Vector(this->x / I, this->y / I); };
    Vector operator+(Vector g) { return Vector(this->x + g.x, this->y + g.y); };
    Vector operator-(Vector g) { return Vector(this->x - g.x, this->y - g.y); };
    friend Vector operator+(int I, Vector f) { return Vector(I + f.x, I + f.y); };
    friend Vector operator-(int I, Vector f) { return Vector(I - f.x, I - f.y); };
    friend Vector operator*(int I, Vector f) { return Vector(I * f.x, I * f.y); };
    friend Vector operator/(int I, Vector f) { return Vector(I / f.x, I / f.y); };
};

class Dot {
public:
    float x, y, mx, my;
    Dot(float x, float y) {
        this->x = x;
        this->y = y;
        this->mx = 0;
        this->my = 0;
    }
    Dot(float x, float y, float mx, float my) {
        this->x = x;
        this->y = y;
        this->mx = mx;
        this->my = my;
    }
    Vector distanceTo(Dot d) {
        return this->distanceTo(Vector(d.x, d.y));
    }
    Vector distanceTo(Vector v) {
        return v - Vector(this->x, this->y);
    }
    Dot clone(void) { return Dot(this->x, this->y, this->mx, this->my); };
    std::string to_string(void) {
        return "x: " + std::to_string(this->x) + ", y: " + std::to_string(this->y) +
               ", mx: " + std::to_string(this->mx) + ", my: " + std::to_string(this->my);
    }
};

class Force {
public:
    float x, y, theta, rho;
    Force(float x, float y) {
        this->x = x;
        this->y = y;
    }
    Force operator+(int I) { return Force(this->x + I, this->y + I); };
    Force operator-(int I) { return Force(this->x - I, this->y - I); };
    Force operator*(int I) { return Force(this->x * I, this->y * I); };
    Force operator/(int I) { return Force(this->x / I, this->y / I); };
    Force operator+(Force g) { return Force(this->x + g.x, this->y + g.y); };
    Force operator-(Force g) { return Force(this->x - g.x, this->y - g.y); };
    Force operator-(void) { return Force(-this->x, -this->y); };
    Force operator+=(Force g) {
        *this = *this + g;
        return *this;
    };
    friend Force operator+(int I, Force f) { return Force(I + f.x, I + f.y); };
    friend Force operator-(int I, Force f) { return Force(I - f.x, I - f.y); };
    friend Force operator*(int I, Force f) { return Force(I * f.x, I * f.y); };
    friend Force operator/(int I, Force f) { return Force(I / f.x, I / f.y); };
    std::string to_string(void) {
        return "fx: " + std::to_string(this->x) + ", fy: " + std::to_string(this->y);
    }
};

class OCDots {
private:
    double m_viscosity = -1.0;

public:
    explicit OCDots(double viscosity);
    ~OCDots() = default;

    [[nodiscard]] double Viscosity() const;
    void SetViscosity(double viscosity);

    std::vector<Dot> movePoints(std::vector<Dot> dots, std::vector<Vector> polygon);
    Force pointForces(Dot d, std::vector<Dot>);
    Force polygonForces(Dot d, std::vector<Vector>);
    Dot updateMomentum(Dot d, Force f);
    bool checkInbounds(Dot d, std::vector<Vector> polygon);
};


#endif//OCPPDOTS_OCDOTS_H
