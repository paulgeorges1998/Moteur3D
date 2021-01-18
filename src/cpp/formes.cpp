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


void triangle(Vec2i A, Vec2i B, Vec2i C, TGAImage &image, TGAColor color) {

    // tri des sommets A, B, C par y croissant
    if (A.y > B.y) std::swap(A, B);
    if (A.y > C.y) std::swap(A, C);
    if (B.y > C.y) std::swap(B, C);

    int hauteurTriangle = C.y - A.y;

    //parcours moitié inférieure
    for(int y = A.y; y <= B.y; y++){
        int hauteurMoitie = B.y - A.y + 1;
        float alpha = (float)(y - A.y)/hauteurTriangle;
        float beta  = (float)(y - A.y)/hauteurMoitie;
        Vec2i pointAC = A + (C - A)*alpha;
        Vec2i pointAB = A + (B - A)*beta;
        if (pointAC.x > pointAB.x) std::swap(pointAC, pointAB);
        // coloriage du segment horizontal
        for(int j = pointAC.x; j <= pointAB.x; j++){
            image.set(j, y, color);
        }
    }

    //parcours moitié supérieure
    for(int y = B.y; y <= C.y; y++){
        int hauteurMoitie =  C.y - B.y + 1;
        float alpha = (float)(y - A.y)/hauteurTriangle;
        float beta  = (float)(y - B.y)/hauteurMoitie;
        Vec2i pointAC = A + (C - A)*alpha;
        Vec2i pointBC = B + (C - B)*beta;
        if(pointAC.x > pointBC.x) std::swap(pointAC, pointBC);
        // coloriage du segment horizontal
        for(int j = pointAC.x; j <= pointBC.x; j++) {
            image.set(j, y, color);
        }
    }
}


