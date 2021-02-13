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
    return floatToInt(proj<3>(gl_Vertex/gl_Vertex[3]));
}

bool Shader::fragment(Vec3f bar, TGAColor &color) {
    float intensity = varying_intensity * bar;
    color = TGAColor(255, 255, 255) * intensity;
    return false;
}

Vec3i Shader::vertexTex(Modele *modele, int i, int n, Matrix VpProjMv, Vec3f lumiere) {
    varying_uv.set_col(n, intToFloat(modele->getuv(i, n)));
    varying_intensity[n] = std::max(0.f, modele->normal(i, n) * lumiere);
    Vec4f gl_Vertex = embed<4>(modele->sommet(i, n));
    gl_Vertex = VpProjMv * gl_Vertex;
    return floatToInt(proj<3>(gl_Vertex/gl_Vertex[3]));
}

bool Shader::fragmentTex(Modele *modele, Vec3f bar, TGAColor &color, Vec3f lumiere) {
    Vec2f uv = varying_uv * bar;
    Vec3f n = proj<3>(MIT * embed<4>(modele->normal(uv))).normalize();
    Vec3f l = proj<3>(M * embed<4>(lumiere)).normalize();
    Vec3f r = (n*(n*l*2.f) - l).normalize();
    float spec = pow(std::max(r.z, 0.0f), std::max(modele->specular(uv), 5.f));
    float intensity = std::max(0.f, n*l);
    TGAColor c = modele->couleurTexture(uv) ;
    for (int i=0; i<3; i++){
        color[i] = std::min<float>(20 + c[i]*(1.5 * intensity + 1 * spec), 255);
    }
    return false;
}
