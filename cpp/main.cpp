#include <stdio.h>
#include <iostream>
#include <cmath>

#include "base.h"




void images(std::string filename){

    int width = 800;
    int height = 800;

    std::string obj = "ressources/" + filename + ".obj";
    std::string fdf = "images/" + filename + "_fdf.tga";
    std::string tri = "images/" + filename + "_triangles.tga";
    std::string tex = "images/" + filename + ".tga";
    std::string buf = "images/" + filename + "_zbuffer.tga";
    std::string sbuf = "images/" + filename + "_shadowbuffer.tga";

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
    TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);
    TGAImage shadowBuffer(width, height, TGAImage::GRAYSCALE);
    trianglesTexture(modele, imageTexture, width, height, zbuffer, shadowBuffer);
    imageTexture.flip_vertically();
    imageTexture.write_tga_file(tex.c_str());
    zbuffer.flip_vertically();
    zbuffer.write_tga_file(buf.c_str());
    shadowBuffer.flip_vertically();
    shadowBuffer.write_tga_file(sbuf.c_str());

}


int main(int argc, char** argv) {

    images("african_head");
    images("diablo3_pose");

    return 0;
}
