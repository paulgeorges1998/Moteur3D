#include <stdio.h>
#include <iostream>
#include <cmath>

#include "base.h"



const int width = 800;
const int height = 800;


int main(int argc, char** argv) {

    Modele *modele = new Modele("ressources/african_head.obj");

    TGAImage imageFdf(width, height, TGAImage::RGB);
    filDeFer(modele, imageFdf, width, height);
    imageFdf.flip_vertically();
    imageFdf.write_tga_file("images/african_head_fdf.tga");

    TGAImage imageTriangles(width, height, TGAImage::RGB);
    triangles(modele, imageTriangles, width, height);
    imageTriangles.flip_vertically();
    imageTriangles.write_tga_file("images/african_head_triangles.tga");

    TGAImage imageTexture(width, height, TGAImage::RGB);
    texture(modele, imageTexture, width, height);
    imageTexture.flip_vertically();
    imageTexture.write_tga_file("images/african_head_texture.tga");

    return 0;
}
