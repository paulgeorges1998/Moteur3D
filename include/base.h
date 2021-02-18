#ifndef BASE_H
#define BASE_H

#include "modele.h"
#include "formes.h"


void filDeFer(Modele *modele, TGAImage &image, int width, int height);

void triangles(Modele *modele, TGAImage &image, int width, int height);

void trianglesTexture(Modele *modele, TGAImage &image, int width, int height, TGAImage &zbuffer, TGAImage &shadowbuffer);

#endif
