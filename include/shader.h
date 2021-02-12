#ifndef SHADER_H
#define SHADER_H

#include "modele.h"


class Shader
{
    public:
        Shader();
        virtual ~Shader();
        Vec3i vertex(Modele *modele, int i, int n, Matrix ProjMv, Matrix vp, Vec3f lumiere);
        Vec3i vertexTex(Modele *modele, int i, int n, Matrix ProjMvVp, Vec3f lumiere);
        bool fragment(Vec3f bar, TGAColor &color);
        bool fragmentTex(Modele *modele, Vec3f bar, TGAColor &color);

    private:
        Vec3f varying_intensity;
        mat<3,3,float> varying_tri;
        mat<2,3,float> varying_uv;

};

#endif // SHADER_H
