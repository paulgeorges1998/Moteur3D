#include "geometry.h"


Vec3f produitVectoriel(Vec3f v1, Vec3f v2){
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = -v1.x * v2.z + v1.z * v2.x;
    float z = v1.x * v2.y - v1.y * v2.x;
    Vec3f r(x, y, z);
    return r;
}

float produitScalaire(Vec3f v1, Vec3f v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
    Vec3f s[2];
    for (int i=2; i--; ) {
        s[i][0] = C[i]-A[i];
        s[i][1] = B[i]-A[i];
        s[i][2] = A[i]-P[i];
    }
    Vec3f u = cross(s[0], s[1]);
    if (std::abs(u[2])>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}
