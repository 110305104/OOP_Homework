#include "sphere.h"

#include <cmath>
#include <iostream>
using namespace std;

Sphere::Sphere() {
    this->orig_x = 0.0;
    this->orig_y = 0.0;
    this->orig_z = 0.0;
    this->radius = 0.0;
}

Sphere::Sphere(float ox, float oy, float oz, float rad) {
    this->orig_x = ox;
    this->orig_y = oy;
    this->orig_z = oz;
    if (rad >= 0)
        this->radius = rad;
    else
        this->radius = 0;
}

float* Sphere::getOrigin() {
    float* result = new float[3]{this->orig_x, this->orig_y, this->orig_z};
    return result;
}

float Sphere::getRadius() {
    return this->radius;
}

void Sphere::setOrigin(float ox, float oy, float oz) {
    this->orig_x = ox;
    this->orig_y = oy;
    this->orig_z = oz;
}

void Sphere::setRadius(float rad) {
    if (rad >= 0)
        this->radius = rad;
    else
        this->radius = 0;
}

bool Sphere::intersect(Sphere& other) {
    float dist = sqrt(pow(this->orig_x - other.orig_x, 2) + pow(this->orig_y - other.orig_y, 2) + pow(this->orig_z - other.orig_z, 2));
    //intersect if(圓心距離<半徑相加)
    if(dist<this->radius+other.radius)
        return true;
    return false;
}

float Sphere::SurfaceArea() {
    return 4 * M_PI * pow(this->radius, 2);
}

float Sphere::Volume() {
    return (4.0 / 3) * M_PI * pow(this->radius, 3);
}

ostream& operator<<(ostream& os, const Sphere& sphere) {
    os << "[( " << sphere.orig_x << ", " << sphere.orig_y << ", " << sphere.orig_z << "), " << sphere.radius << "]";
    return os;
}