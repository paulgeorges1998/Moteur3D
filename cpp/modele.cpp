#include "modele.h"

Modele::Modele(const char *filename) : sommets(), faces()
{
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            sommets.push_back(v);
        } else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vec2f v;
            for (int i=0;i<2;i++) iss >> v[i];
            uv.push_back(v);
        } else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vec3f n;
            for (int i=0;i<3;i++) iss >> n[i];
            norms.push_back(n);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            Vec3i tmp;
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i=0; i<3; i++) tmp[i]--;
                f.push_back(tmp);
            }
            faces.push_back(f);
        }
    }

    load_texture(filename, "_diffuse.tga", diffusemap);
    load_texture(filename, "_nm.tga", normalmap);
}

Modele::~Modele()
{

}

void Modele::load_texture(std::string filename, const char *suffix, TGAImage &img) {
    std::string texfile(filename);
    size_t dot = texfile.find_last_of(".");
    if (dot!=std::string::npos) {
        texfile = texfile.substr(0,dot) + std::string(suffix);
        std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
        img.flip_vertically();
    }
}

int Modele::nSommets() {
    return (int)sommets.size();
}

int Modele::nFaces() {
    return (int)faces.size();
}


std::vector<int> Modele::face(int idx) {
    std::vector<int> face;
    for (int i=0; i<(int)faces[idx].size(); i++) face.push_back(faces[idx][i][0]);
    return face;
}

Vec3f Modele::sommet(int i) {
    return sommets[i];
}

Vec3f Modele::sommet(int i, int n) {
    return sommets[faces[i][n][0]];
}

TGAColor Modele::couleurTexture(Vec2i uv) {
    return diffusemap.get(uv.x, uv.y);
}

Vec2i Modele::getuv(int face, int sommet) {
    int idx = faces[face][sommet][1];
    return Vec2i(uv[idx].x * diffusemap.get_width(), uv[idx].y * diffusemap.get_height());
}

Vec3f Modele::normal(Vec2f uvf) {
    Vec2i uv(uvf[0]*normalmap.get_width(), uvf[1]*normalmap.get_height());
    TGAColor c = normalmap.get(uv[0], uv[1]);
    Vec3f res;
    for (int i=0; i<3; i++)
        res[2-i] = (float)c[i]/255.f*2.f - 1.f;
    return res;
}

Vec3f Modele::normal(int iface, int nthvert) {
    int idx = faces[iface][nthvert][2];
    return norms[idx].normalize();
}
