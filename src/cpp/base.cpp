#include "base.h"

void filDeFer(Modele *modele, TGAImage &image, int width, int height){

    for (int i=0; i<modele->nFaces(); i++) {
        std::vector<int> face = modele->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = modele->sommet(face[j]);
            Vec3f v1 = modele->sommet(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            ligne(x0, y0, x1, y1, image, TGAImage::BLANC);
        }
    }
}

void triangles(Modele *modele, TGAImage &image, int width, int height){

    for (int i=0; i<modele->nFaces(); i++) {
        std::vector<int> face = modele->face(i);
        Vec2i coords_ecran[3];
        for (int j = 0; j < 3; j++) {
            Vec3f coords = modele->sommet(face[j]);
            coords_ecran[j] = Vec2i((coords.x + 1.)*width/2., (coords.y + 1.)*height/2.);
        }
        triangle(coords_ecran[0], coords_ecran[1], coords_ecran[2], image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
    }
}
