
#include "world.h"
#include "config.h"

int world::GetImageWidth(){
    return pconfig->IMAGE_WIDTH;
}
int world::GetImageHeight(){
    return pconfig->IMAGE_HEIGHT;
}

double world::GetAspectRatio(){
    return pconfig->ASPECT_RATIO;
}

int world::GetSamplesPerPixel(){
    return pconfig->SAMPLES_PER_PIXEL;
}

int world::GetMaxDepth(){
    return pconfig->MAX_DEPTH;
}

bool world::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{

    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;

}