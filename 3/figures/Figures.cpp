#include "Figures.h"

bool Polygon::operator==(const Polygon& obj) const {
    if (GetVertices().size() != obj.GetVertices().size()) {
        return false;
    }

    auto size = GetVertices().size();
    for (int i = 0, j = 0; j < size; ++j) {
        if (i == size) {
            return true;
        } else if (vertices[i] == obj.vertices[j]) {
            ++i;
            j = -1;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Polygon& figure) {
    os << figure.GetName() << ": " << " { ";
    for (auto& v : figure.vertices) {
        os << v;
    }
    os << "}";

    return os;
}