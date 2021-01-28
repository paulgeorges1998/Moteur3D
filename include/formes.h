#ifndef FORMES_H
#define FORMES_H

#include "tgaimage.h"
#include "geometry.h"
#include "base.h"
#include <limits>

void ligne(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Vec3f *pts, float *zbuffer, int width, int height, TGAImage &image, TGAColor color);

void triangleTexture(Modele *modele, Vec3f *pts, Vec2i *pts2, float *zbuffer, int width, int height, TGAImage &image, float intensity);

#endif // FORMES_H
