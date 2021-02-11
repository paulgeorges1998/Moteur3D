#include "shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
}


Vec3i Shader::vertex(Modele *modele, int i, int n, Matrix ProjMv, Matrix vp, Vec3f lumiere) {

    Vec4f gl_Vertex = embed<4>(modele->sommet(i, n));
    gl_Vertex = ProjMv * gl_Vertex;
    varying_tri.set_col(n, proj<3>(gl_Vertex/gl_Vertex[3]));
    varying_intensity[n] = CLAMP(modele->normal(i, n)*lumiere, 0.f, 1.f);
    gl_Vertex = vp * gl_Vertex;
    Vec4f v = gl_Vertex/gl_Vertex[3];
    return floatToInt(proj<3>(gl_Vertex/gl_Vertex[3]));
}

bool Shader::fragment(Vec3f bar, TGAColor &color) {
    float intensity = varying_intensity * bar;
    color = TGAColor(255, 255, 255) * intensity;
    return false;

}
