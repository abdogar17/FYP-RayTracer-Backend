#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double EPSILON = 0.00001;
const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif