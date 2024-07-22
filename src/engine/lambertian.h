#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "hittable.h"
#include "../util/vec3.h"

class lambertian : public material {
    public:
        lambertian(const color& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override ;

    public:
        color albedo;
};

#endif
