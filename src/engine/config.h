#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include "hittable.h"

class config {
    public:
        config() {}

    public:
        int IMAGE_WIDTH;
        double ASPECT_RATIO;
        int IMAGE_HEIGHT;
        int SAMPLES_PER_PIXEL;
        int MAX_DEPTH;
};


#endif
