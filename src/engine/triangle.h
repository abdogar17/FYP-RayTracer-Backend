#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class triangle : public hittable {
    public:
        triangle() {}
        triangle(const vec3 & v0, const vec3 & v1, const vec3 & v2, shared_ptr<material> mat_ptr);
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        vec3 v0, v1, v2;
        shared_ptr<material> mat_ptr;
};


#endif
