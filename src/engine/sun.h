#ifndef SUN_H
#define SUN_H

#include "hittable.h"

class sun{
    public:
        sun() {}
        sun(const vec3 & direction, const color & pcolor);

    public:
        vec3 direction;
        color sunColor;
};


#endif
