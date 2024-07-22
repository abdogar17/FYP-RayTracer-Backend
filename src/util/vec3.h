#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include "util.h"

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        bool near_zero() const;
        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);

        vec3& operator+=(const vec3 &v);
        vec3& operator*=(const double t);
        vec3& operator/=(const double t);

        double length() const;
        double length_squared() const;

        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }

    public:
        double e[3];
};

std::ostream& operator<<(std::ostream &out, const vec3 &v);
vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, const vec3 &v);
vec3 operator*(double t, const vec3 &v);
vec3 operator*(const vec3 &v, double t);
vec3 operator/(vec3 v, double t);
double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 unit_vector(vec3 v);
vec3 random_in_unit_sphere();
vec3 random_unit_vector();
vec3 random_in_hemisphere(const vec3& normal);
vec3 reflect(const vec3& v, const vec3& n);
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

#endif