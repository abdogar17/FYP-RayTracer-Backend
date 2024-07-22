#ifndef CAMERA_H
#define CAMERA_H

#include "../util/vec3.h"
#include "../util/ray.h"

class camera {
    public:
        camera() {}
        
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio
        );
        ray get_ray(double u, double v) const;

    public:
        double VIEWPORT_WIDTH;
        double VIEWPORT_HEIGHT;
        double FOCAL_LENGTH;

        // Not used in the actual Camera Algorithms.
        //  Mostly for debugging and reference :
        point3 LOOK_FROM;
        point3 LOOK_AT;
        vec3   UP;
        double FOV; // vertical field-of-view in degrees
        double ASPECT_RATIO;

    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;

};

#endif
