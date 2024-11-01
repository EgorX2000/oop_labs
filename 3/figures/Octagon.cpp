#include "Figures.h"

std::vector<Vertex> Octagon::MakeVertices(const Vertex& v, double sideLen) {
    std::vector<Vertex> verts;

    verts.push_back(v);
    verts.push_back({v.x, v.y + sideLen});
    verts.push_back({v.x + sideLen * cos(M_PI / 4),
                     v.y + sideLen + sideLen * sin(M_PI / 4)});
    verts.push_back({v.x + sideLen * cos(M_PI / 4) + sideLen,
                     v.y + sideLen + sideLen * sin(M_PI / 4)});
    verts.push_back(
        {v.x + sideLen * cos(M_PI / 4) + sideLen + sideLen * cos(M_PI / 4),
         v.y + sideLen});
    verts.push_back(
        {v.x + sideLen * cos(M_PI / 4) + sideLen + sideLen * cos(M_PI / 4),
         v.y});
    verts.push_back({v.x + sideLen * cos(M_PI / 4) + sideLen,
                     v.y - sideLen * sin(M_PI / 4)});
    verts.push_back(
        {v.x + sideLen * cos(M_PI / 4), v.y - sideLen * sin(M_PI / 4)});

    return verts;
}

Vertex Octagon::GetCenter() const {
    double centerX =
        (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x +
         vertices[4].x + vertices[5].x + vertices[6].x + vertices[7].x) /
        8;
    double centerY =
        (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y +
         vertices[4].y + vertices[5].y + vertices[6].y + vertices[7].y) /
        8;

    return Vertex{centerX, centerY};
}

double Octagon::GetArea() const { return 2 * (1 + sqrt(2)) * pow(sideLen, 2); }

Octagon::operator double() const { return GetArea(); }

bool Octagon::operator==(const Octagon& obj) const {
    for (int i = 0, j = 0; j < 8; j++) {
        if (i == 8) {
            return true;
        } else if (vertices[i] == obj.vertices[j]) {
            i++;
            j = -1;
        }
    }
    return false;
}

std::istream& operator>>(std::istream& is, Octagon& obj) {
    is >> obj.pos;
    is >> obj.sideLen;

    return is;
}
