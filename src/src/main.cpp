#include <stdio.h>
#include <iostream>
#include <cmath>

#include "base.h"



const int width = 800;
const int height = 800;


int main(int argc, char** argv) {

    TGAImage image(width, height, TGAImage::RGB);

    Modele *modele = new Modele("ressources/african_head.obj");

    filDeFer(modele, image, width, height);

    image.flip_vertically();
    image.write_tga_file("images/african_head.tga");

    return 0;
}
