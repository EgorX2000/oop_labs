#include <iostream>

#include "figures/Figures.cpp"

int main() {
    Octagon<double> oct{{0, 0}, 1};
    Triangle<double> tri{{0, 0}, 1};
    Square<double> sqr{{0, 0}, 1};

    std::cout << oct.GetCenter() << std::endl;
    std::cout << tri.GetCenter() << std::endl;
    std::cout << sqr.GetCenter() << std::endl;

    /*
    std::vector<Vertex> verts = tri.GetVertices();
    for (int i = 0; i < verts.size(); i++) {
        std::cout << verts[i] << std::endl;
    }
    */

    return 0;
}