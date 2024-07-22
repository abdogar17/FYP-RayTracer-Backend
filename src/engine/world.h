#ifndef WORLD_H
#define WORLD_H

#include <vector>
//#include <memory>
#include "hittable.h"
//#include "sun.h"

class sun;
//class hittable;
class camera;
class config;
class material;

class world : public hittable {
    public:
        world() {}
        int GetImageWidth();
        int GetImageHeight();
        double GetAspectRatio();
        int GetSamplesPerPixel();
        int GetMaxDepth();

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        std::shared_ptr<config> pconfig;
        std::shared_ptr<sun> psun;
        std::shared_ptr<camera> pcamera;
        std::vector< std::shared_ptr<material> > materials;
        std::vector< std::shared_ptr<hittable> > objects;
};


#endif
