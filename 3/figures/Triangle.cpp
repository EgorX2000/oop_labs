#include "Figures.h"

std::vector<Vertex> Triangle::MakeVertices(const Vertex& v, double sideLen) {
    std::vector<Vertex> verts;

    verts.push_back(v);
    verts.push_back(
        {v.x + sideLen * cos(M_PI / 3), v.y + sideLen * sin(M_PI / 3)});
    verts.push_back({v.x + sideLen, v.y});

    return verts;
}

Vertex Triangle::GetCenter() const {
    double centerX = (vertices[0].x + vertices[1].x + vertices[2].x) / 3;
    double centerY = (vertices[0].y + vertices[1].y + vertices[2].y) / 3;

    return Vertex{centerX, centerY};
}

double Triangle::GetArea() const { return sqrt(3) / 4 * pow(sideLen, 2); }

Triangle::operator double() const { return GetArea(); }

bool Triangle::operator==(const Triangle& obj) const {
    for (int i = 0, j = 0; j < 3; j++) {
        if (i == 3) {
            return true;
        } else if (vertices[i] == obj.vertices[j]) {
            i++;
            j = -1;
        }
    }
    return false;
}

std::istream& operator>>(std::istream& is, Triangle& obj) {
    std::vector<Vertex> verts;

    is >> obj.pos;
    is >> obj.sideLen;

    return is;
}