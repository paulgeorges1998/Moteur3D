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

    float *zbuffer = new float[height * width];
    for(int i = 0; i < height * width; i++){
        zbuffer[i] = INT_MIN;
    }

    for (int i=0; i<modele->nFaces(); i++) {
        std::vector<int> face = modele->face(i);
        Vec3f coords_ecran[3];
        Vec3f coords_monde[3];
        for (int j = 0; j < 3; j++){
            Vec3f coords = modele->sommet(face[j]);
            coords_ecran[j] = Vec3f(int((coords.x+1.)*width/2.+.5), int((coords.y+1.)*height/2.+.5), coords.z);
            coords_monde[j] = coords;
        }

        Vec3f n = produitVectoriel(coords_monde[2]-coords_monde[0], coords_monde[1]-coords_monde[0]);
        n.normalize();
        Vec3f lumiere(0, 0, -1);
        float intensity = produitScalaire(n, lumiere);
        if (intensity > 0) {
            triangle(coords_ecran, zbuffer, width, height, image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
        }
    }
}


void texture(Modele *modele, TGAImage &image, int width, int height){

    float *zbuffer = new float[height * width];
    for(int i = 0; i < height * width; i++){
        zbuffer[i] = INT_MIN;
    }

    for (int i=0; i<modele->nFaces(); i++) {
        std::vector<int> face = modele->face(i);
        Vec3f coords_ecran[3];
        Vec3f coords_monde[3];
        for (int j = 0; j < 3; j++){
            Vec3f coords = modele->sommet(face[j]);
            coords_ecran[j] = Vec3f(int((coords.x+1.)*width/2.+.5), int((coords.y+1.)*height/2.+.5), coords.z);
            coords_monde[j] = coords;
        }

        Vec3f n = produitVectoriel(coords_monde[2]-coords_monde[0], coords_monde[1]-coords_monde[0]);
        n.normalize();
        Vec3f lumiere(0, 0, -1);
        float intensity = produitScalaire(n, lumiere);
        if (intensity > 0) {
            Vec2i uv[3];
            for(int j = 0; j < 3; j++){
                uv[j] = modele->getuv(i, j);
            }
            triangleTexture(modele, coords_ecran, uv, zbuffer, width, height, image, intensity);
        }
    }
}
