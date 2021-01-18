#ifndef FORMES_H
#define FORMES_H

#include "tgaimage.h"
#include "geometry.h"

void ligne(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vec2i A, Vec2i B, Vec2i C, TGAImage &image, TGAColor color);


#endif // FORMES_H
