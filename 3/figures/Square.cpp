#include "Figures.h"

std::vector<Vertex> Square::MakeVertices(const Vertex& v, double sideLen) {
    std::vector<Vertex> verts;

    verts.push_back(v);
    verts.push_back({v.x + sideLen, v.y});
    verts.push_back({v.x, v.y + sideLen});
    verts.push_back({v.x + sideLen, v.y + sideLen});

    return verts;
}

Vertex Square::GetCenter() const {
    return Vertex{pos.x + sideLen * 0.5, pos.y + sideLen * 0.5};
}

double Square::GetArea() const { return pow(sideLen, 2); }

Square::operator double() const { return GetArea(); }

bool Square::operator==(const Square& obj) const {
    return sideLen == obj.sideLen && pos == obj.pos;
}

std::istream& operator>>(std::istream& is, Square& obj) {
    is >> obj.pos;
    is >> obj.sideLen;

    return is;
}