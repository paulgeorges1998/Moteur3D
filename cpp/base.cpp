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

    TGAImage zbuffer(width, height, TGAImage::GRAYSCALE);
    Vec3f camera = Vec3f(2, 0, 3);
    Vec3f centre = Vec3f(0, 0, 0);
    Vec3f u = Vec3f(0, 1, 0);

    Vec3f lumiere(0, 1, 1);
    lumiere.normalize();
    Matrix proj = Matrix::identity();
    Matrix vp = viewport(width/8, height/8, width*3/4, height*3/4);
    Matrix modelview = lookat(camera, centre, u);
    proj[3][2] = -1.f/((camera - centre).norm());

    for (int i=0; i<modele->nFaces(); i++) {
        std::vector<int> face = modele->face(i);
        Vec3i coords_ecran[3];
        Vec3f coords_monde[3];
        Shader shader;
        for (int j = 0; j < 3; j++){
            coords_ecran[j] = shader.vertex(modele, i, j, proj * modelview, vp, lumiere);

        }
        triangle(shader, coords_ecran, zbuffer, width, height, image);
    }
}



void trianglesTexture(Modele *modele, TGAImage &image, int width, int height){

    Vec3f camera = Vec3f(2, 0, 3);
    Vec3f centre = Vec3f(0, 0, 0);
    Vec3f u = Vec3f(0, 1, 0);

    float *zbuffer = new float[height * width];
    for(int i = 0; i < height * width; i++){
        zbuffer[i] = INT_MIN;
    }

    Matrix proj = Matrix::identity();
    Matrix vp = viewport(width/8, height/8, width*3/4, height*3/4);
    proj[3][2] = -1.f/(camera - centre).norm();

    for (int i=0; i<modele->nFaces(); i++) {
        std::vector<int> face = modele->face(i);
        Vec3i coords_ecran[3];
        Vec3f coords_monde[3];
        for (int j = 0; j < 3; j++){
            Vec3f coords = modele->sommet(face[j]);
            Matrix modelview = lookat(camera, centre, u);
            coords_ecran[j] = floatToInt(m2v(vp * proj * modelview * v2m(coords)));
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
