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

    Vec3i coords_ecran[3];
    Shader shader;
    for (int i=0; i<modele->nFaces(); i++) {
        for (int j = 0; j < 3; j++){
            coords_ecran[j] = shader.vertex(modele, i, j, proj * modelview, vp, lumiere);
        }
        triangle(shader, coords_ecran, zbuffer, width, height, image);
    }
}



void trianglesTexture(Modele *modele, TGAImage &image, int width, int height, TGAImage &zbuffer, TGAImage &shadowbuffer){


    Vec3f camera = Vec3f(2, 0, 3);
    Vec3f centre = Vec3f(0, 0, 0);
    Vec3f haut = Vec3f(0, 1, 0);
    Vec3f lumiere(0, 1, 1);
    lumiere.normalize();
    Matrix vp = viewport(width/8, height/8, width*3/4, height*3/4);
    Matrix modelview = lookat(lumiere, centre, haut);
    Matrix proj = Matrix::identity();
    Matrix MS = vp * proj * modelview;

    Vec3i coords_ecran[3];
    Shader shader;
    shader.VpProjMv = MS;
    for (int i=0; i<modele->nFaces(); i++) {
        for (int j = 0; j < 3; j++){
            coords_ecran[j] = shader.vertexShadow(modele, i, j);
        }
        triangleTexture(shader, lumiere, modele, coords_ecran, width, height, shadowbuffer, shadowbuffer, true);
    }

    modelview = lookat(camera, centre, haut);
    proj[3][2] = -1.f/((camera - centre).norm());


    Shader shader2;
    shader2.M = modelview;
    shader2.MIT = (proj * modelview).invert_transpose();
    shader2.VpProjMv = vp * proj * modelview;
    shader2.MS = MS * ((shader2.VpProjMv).invert());
    shader2.shadowbuffer = TGAImage(shadowbuffer);
    for (int i=0; i<modele->nFaces(); i++) {
        for (int j = 0; j < 3; j++){
            coords_ecran[j] = shader2.vertexTex(modele, i, j, lumiere);
        }
        triangleTexture(shader2, lumiere, modele, coords_ecran, width, height, image, zbuffer, false);
    }
}
