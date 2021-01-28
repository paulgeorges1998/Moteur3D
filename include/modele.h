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
        std::vector<int> face(int i);
        int nSommets();
        int nFaces();
        TGAColor couleurTexture(Vec2i uv);
        Vec2i getuv(int face, int sommet);


    private:
        std::vector<Vec3f> sommets;
        std::vector<std::vector<Vec3i> > faces;
        std::vector<Vec2f> uv;
        TGAImage diffusemap;

};

#endif // MODELE_H
