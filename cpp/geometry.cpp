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
    if (std::abs(u[2])>1e-2)
        return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    return Vec3f(-1,1,1);
}



Vec3f m2v(Matrix m) {
    return Vec3f(m[0][0]/m[3][0], m[1][0]/m[3][0], m[2][0]/m[3][0]);
}

Matrix v2m(Vec3f v) {
    Matrix m;
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1.f;
    return m;
}

Matrix viewport(int x, int y, int w, int h) {
    Matrix m = Matrix::identity();
    m[0][3] = x+w/2.f;
    m[1][3] = y+h/2.f;
    m[2][3] = 255/2.f;
    m[0][0] = w/2.f;
    m[1][1] = h/2.f;
    m[2][2] = 255/2.f;
    return m;
}

Matrix lookat(Vec3f camera, Vec3f centre, Vec3f u) {
    Vec3f z = (camera - centre).normalize();
    Vec3f x = cross(u,z).normalize();
    Vec3f y = cross(z,x).normalize();
    Matrix Minv = Matrix::identity();
    Matrix Tr   = Matrix::identity();
    for (int i=0; i<3; i++) {
        Minv[0][i] = x[i];
        Minv[1][i] = y[i];
        Minv[2][i] = z[i];
        Tr[i][3] = -centre[i];
    }
    return Minv*Tr;
}

Vec3i floatToInt(Vec3f vf){
    Vec3i v;
    v.x = (int)vf.x;
    v.y = (int)vf.y;
    v.z = (int)vf.z;
    return v;
}

Vec3f intToFloat(Vec3i vi){
    Vec3f v;
    v.x = vi.x + 0.5;
    v.y = vi.y + 0.5;
    v.z = vi.z + 0.5;
    return v;
}






