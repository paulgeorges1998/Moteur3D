#include "formes.h"



void ligne(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
}


void triangle(Shader shader, Vec3i *pts, TGAImage &zbuffer, int width, int height, TGAImage &image) {
    Vec2i bboxmin( std::numeric_limits<int>::max(),  std::numeric_limits<int>::max());
    Vec2i bboxmax(-std::numeric_limits<int>::max(), -std::numeric_limits<int>::max());
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            bboxmin[j] = std::min(bboxmin[j], pts[i][j]);
            bboxmax[j] = std::max(bboxmax[j], pts[i][j]);
        }
    }
    Vec3i P;
    TGAColor color;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vec3f bc_screen = barycentric(intToFloat(pts[0]), intToFloat(pts[1]), intToFloat(pts[2]), intToFloat(P));
            P.z = std::max(0, std::min(255, int(pts[0].z * bc_screen.x + pts[1].z * bc_screen.y + pts[2].z * bc_screen.z + .5)));
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0 || zbuffer.get(P[0], P[1])[0]>P[2]) continue;
            bool discard = shader.fragment(bc_screen, color);
            if (!discard) {
                zbuffer.set(P.x, P.y, TGAColor(P[2]));
                image.set(P.x, P.y, color);
            }
        }
    }
}



void triangleTexture(Shader shader, Modele *modele, Vec3i *pts, TGAImage &zbuffer, int width, int height, TGAImage &image) {
    Vec2i bboxmin( std::numeric_limits<int>::max(),  std::numeric_limits<int>::max());
    Vec2i bboxmax(-std::numeric_limits<int>::max(), -std::numeric_limits<int>::max());
    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            bboxmin[j] = std::min(bboxmin[j], pts[i][j]);
            bboxmax[j] = std::max(bboxmax[j], pts[i][j]);
        }
    }
    Vec3i P;
    TGAColor color;
    for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
        for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
            Vec3f bc_screen = barycentric(intToFloat(pts[0]), intToFloat(pts[1]), intToFloat(pts[2]), intToFloat(P));
            P.z = std::max(0, std::min(255, int(pts[0].z * bc_screen.x + pts[1].z * bc_screen.y + pts[2].z * bc_screen.z + .5)));
            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0 || zbuffer.get(P[0], P[1])[0]>P[2]) continue;
            bool discard = shader.fragmentTex(modele, bc_screen, color);
            if (!discard) {
                zbuffer.set(P.x, P.y, TGAColor(P[2]));
                image.set(P.x, P.y, color);
            }
        }
    }

}
