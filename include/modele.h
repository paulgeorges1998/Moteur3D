#ifndef MODELE_H
#define MODELE_H

#include <vector>
#include <fstream>
#include "geometry.h"
#include "tgaimage.h"

class Modele
{
    public:
        Modele(const char *filename);
        virtual ~Modele();
        Vec3f sommet(int i);
        Vec3f sommet(int i, int n);
        std::vector<int> face(int i);
        int nSommets();
        int nFaces();
        TGAColor couleurTexture(Vec2f uv);
        Vec2i getuv(int face, int sommet);
        TGAColor diffuse(Vec2f uvf);
        Vec3f normal(Vec2f uvf);
        Vec3f normal(int iface, int nthvert);
        float specular(Vec2f uvf);




    private:
        std::vector<Vec3f> sommets;
        std::vector<std::vector<Vec3i> > faces;
        std::vector<Vec2f> uv;
        std::vector<Vec3f> norms;
        TGAImage diffusemap;
        TGAImage normalmap;
        TGAImage specularmap;
        void load_texture(std::string filename, const char *suffix, TGAImage &img);

};

#endif // MODELE_H
