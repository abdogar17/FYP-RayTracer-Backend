
#include "triangle.h"

triangle::triangle(const vec3 & v0, const vec3 & v1, const vec3 & v2, shared_ptr<material> mat_ptr){
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    this->mat_ptr = mat_ptr;
}

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    
    // compute plane's normal
    vec3 v0v1 = v1 - v0; 
    vec3 v0v2 = v2 - v0; 
    // no need to normalize
    vec3 N = cross(v0v1, v0v2);  //N 
    float area2 = N.length(); 

    // Step 1: finding P
 
    // check if ray and plane are parallel ?
    float NdotRayDirection = dot(N, r.dir);
    if (fabs(NdotRayDirection) < EPSILON)  //almost 0 
        return false;  //they are parallel so they don't intersect !

    // compute d parameter using equation 2
    float d = -dot(N, v0);
 
    // compute t (equation 3)
    double t = -(dot(N, r.orig) + d) / NdotRayDirection; 
 
    // check if the triangle is in behind the ray
    if (t < 0) return false;  //the triangle is behind 
 
    // compute the intersection point using equation 1
    vec3 P = r.orig + t * r.dir; 

    // Step 2: inside-outside test
    vec3 C;  //vector perpendicular to triangle's plane 
 
    // edge 0
    vec3 edge0 = v1 - v0; 
    vec3 vp0 = P - v0; 
    C = cross(edge0,vp0); 
    if (dot(N,C) < 0) return false;  //P is on the right side 
 
    // edge 1
    vec3 edge1 = v2 - v1; 
    vec3 vp1 = P - v1; 
    C = cross(edge1,vp1); 
    if (dot(N,C) < 0)  return false;  //P is on the right side 
 
    // edge 2
    vec3 edge2 = v0 - v2; 
    vec3 vp2 = P - v2; 
    C = cross(edge2,vp2); 
    if (dot(N,C) < 0) return false;  //P is on the right side; 
 
    rec.p = P;
    rec.t = t;
    rec.normal = N;
    rec.mat_ptr = mat_ptr;

    return true;  //this ray hits the triangle 
}

// bool rayTriangleIntersect( 
//     const Vec3f &orig, const Vec3f &dir, 
//     const Vec3f &v0, const Vec3f &v1, const Vec3f &v2, 
//     float &t) 
// { 
//     // // compute plane's normal
//     // Vec3f v0v1 = v1 - v0; 
//     // Vec3f v0v2 = v2 - v0; 
//     // // no need to normalize
//     // Vec3f N = v0v1.crossProduct(v0v2);  //N 
//     // float area2 = N.length(); 
 
//     // // Step 1: finding P
 
//     // // check if ray and plane are parallel ?
//     // float NdotRayDirection = N.dotProduct(dir); 
//     // if (fabs(NdotRayDirection) < kEpsilon)  //almost 0 
//     //     return false;  //they are parallel so they don't intersect ! 
 
//     // // compute d parameter using equation 2
//     // float d = -N.dotProduct(v0); 
 
//     // // compute t (equation 3)
//     // t = -(N.dotProduct(orig) + d) / NdotRayDirection; 
 
//     // // check if the triangle is in behind the ray
//     // if (t < 0) return false;  //the triangle is behind 
 
//     // // compute the intersection point using equation 1
//     // Vec3f P = orig + t * dir; 
 
//     // // Step 2: inside-outside test
//     // Vec3f C;  //vector perpendicular to triangle's plane 
 
//     // // edge 0
//     // Vec3f edge0 = v1 - v0; 
//     // Vec3f vp0 = P - v0; 
//     // C = edge0.crossProduct(vp0); 
//     // if (N.dotProduct(C) < 0) return false;  //P is on the right side 
 
//     // // edge 1
//     // Vec3f edge1 = v2 - v1; 
//     // Vec3f vp1 = P - v1; 
//     // C = edge1.crossProduct(vp1); 
//     // if (N.dotProduct(C) < 0)  return false;  //P is on the right side 
 
//     // // edge 2
//     // Vec3f edge2 = v0 - v2; 
//     // Vec3f vp2 = P - v2; 
//     // C = edge2.crossProduct(vp2); 
//     // if (N.dotProduct(C) < 0) return false;  //P is on the right side; 
 
//     // return true;  //this ray hits the triangle 
// } 