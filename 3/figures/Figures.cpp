bool Polygon::operator==(const Polygon& rhs) const {
    if (GetVertices().size() != rhs.GetVertices().size()) {
        return false;
    }

    auto size = GetVertices().size();
    for (int i = 0, j = 0; j < size; ++j) {
        if (i == size) {
            return true;
        } else if (vertices[i] == rhs.vertices[j]) {
            ++i;
            j = -1;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Polygon& shape) {
    os << shape.GetName() << ": " << " { ";
    for (auto& v : shape.vertices) {
        os << v;
    }
    os << "}";

    return os;
}