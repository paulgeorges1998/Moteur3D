#include <stdio.h>
#include <iostream>
#include <cmath>

#include "base.h"



const int width = 800;
const int height = 800;


void images(std::string filename){

    std::string obj = "ressources/" + filename + ".obj";
    std::string fdf = "images/" + filename + "_fdf.tga";
    std::string tri = "images/" + filename + "_triangles.tga";
    std::string tex = "images/" + filename + "_texture.tga";

    Modele *modele = new Modele(obj.c_str());

    TGAImage imageFdf(width, height, TGAImage::RGB);
    filDeFer(modele, imageFdf, width, height);
    imageFdf.flip_vertically();
    imageFdf.write_tga_file(fdf.c_str());

    TGAImage imageTriangles(width, height, TGAImage::RGB);
    triangles(modele, imageTriangles, width, height);
    imageTriangles.flip_vertically();
    imageTriangles.write_tga_file(tri.c_str());

    TGAImage imageTexture(width, height, TGAImage::RGB);
    texture(modele, imageTexture, width, height);
    imageTexture.flip_vertically();
    imageTexture.write_tga_file(tex.c_str());

}


int main(int argc, char** argv) {

    images("african_head");
    images("diablo3_pose");

    return 0;
}
