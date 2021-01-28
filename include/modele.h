#ifndef MODELE_H
#define MODELE_H

#include <vector>
#include <fstream>
#include "geometry.h"

class Modele
{
    public:
        Modele(const char *filename);
        virtual ~Modele();
        Vec3f sommet(int i);
        std::vector<int> face(int i);
        int nSommets();
        int nFaces();

    private:
        std::vector<Vec3f> sommets;
        std::vector<std::vector<int> > faces;
};

#endif // MODELE_H
