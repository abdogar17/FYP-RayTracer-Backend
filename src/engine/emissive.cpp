
#include "emissive.h"
#include "hittable.h"
#include "../util/vec3.h"

bool emissive::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
    //vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    //scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
    attenuation = pcolor*100;
    return false;
}