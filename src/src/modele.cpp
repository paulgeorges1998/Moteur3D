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
            for (int i=0;i<3;i++) iss >> v.raw[i];
            sommets.push_back(v);
        } else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--;
                f.push_back(idx);
            }
            faces.push_back(f);
        }
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


std::vector<int> Modele::face(int i) {
    return faces[i];
}

Vec3f Modele::sommet(int i) {
    return sommets[i];
}
