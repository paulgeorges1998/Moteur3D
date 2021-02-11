#ifndef FORMES_H
#define FORMES_H

#include "shader.h"
#include "base.h"
#include <limits>

void ligne(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

void triangle(Shader shader, Vec3i *pts, TGAImage &zbuffer, int width, int height, TGAImage &image);

void triangleTexture(Modele *modele, Vec3i *pts, Vec2i *pts2, float *zbuffer, int width, int height, TGAImage &image, float intensity);

#endif // FORMES_H
