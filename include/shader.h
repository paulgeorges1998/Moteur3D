#ifndef SHADER_H
#define SHADER_H

#include "modele.h"


class Shader
{
    public:
        Shader();
        virtual ~Shader();
        Vec3i vertex(Modele *modele, int i, int n, Matrix ProjMv, Matrix vp, Vec3f lumiere);
        Vec3i vertexTex(Modele *modele, int i, int n, Vec3f lumiere);
        Vec3i vertexShadow(Modele *modele, int i, int n);
        bool fragment(Vec3f bar, TGAColor &color);
        bool fragmentTex(Modele *modele, Vec3f bar, TGAColor &color, Vec3f lumiere, int width);
        bool fragmentShadow(Vec3f barycentre, TGAColor &color);
        Matrix M;
        Matrix MIT;
        Matrix MS;
        Matrix VpProjMv;
        TGAImage shadowbuffer;

    private:
        Vec3f varying_intensity;
        mat<3,3,float> varying_tri;
        mat<2,3,float> varying_uv;


};

#endif // SHADER_H
