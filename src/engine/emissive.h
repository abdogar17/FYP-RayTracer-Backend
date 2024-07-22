#ifndef EMISSIVE_H
#define EMISSIVE_H

#include "material.h"

class emissive : public material {
    public:
        emissive(const color& c) : pcolor(c) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override ;

    public:
        color pcolor;
};

#endif
