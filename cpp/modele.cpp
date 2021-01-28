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

    std::string texfile(filename);
    size_t dot = texfile.find_last_of(".");
    if (dot!=std::string::npos) {
        texfile = texfile.substr(0,dot) + std::string("_diffuse.tga");
        std::cerr << "texture file " << texfile << " loading " << (diffusemap.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
        diffusemap.flip_vertically();
    }
}

Modele::~Modele()
{

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

TGAColor Modele::couleurTexture(Vec2i uv) {
    return diffusemap.get(uv.x, uv.y);
}

Vec2i Modele::getuv(int face, int sommet) {
    int idx = faces[face][sommet][1];
    return Vec2i(uv[idx].x * diffusemap.get_width(), uv[idx].y * diffusemap.get_height());
}
