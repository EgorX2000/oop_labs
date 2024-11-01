#include <iostream>

#include "figures/Figures.h"

int main() {
    Octagon oct{{0, 0}, 1};
    Triangle tri{{0, 0}, 1};
    Square sqr{{0, 0}, 1};

    std::cout << oct.GetName() << oct.GetCenter() << std::endl;
    std::cout << tri.GetName() << tri.GetCenter() << std::endl;
    std::cout << sqr.GetName() << sqr.GetCenter() << std::endl;

    /*
    std::vector<Vertex> verts = tri.GetVertices();
    for (int i = 0; i < verts.size(); i++) {
        std::cout << verts[i] << std::endl;
    }
    */

    return 0;
}