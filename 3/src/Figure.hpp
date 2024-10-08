#pragma once

#include <iostream>
#include <vector>

class Figure {
   public:
    std::string get_geometric_center() const { return; }
    std::string get_vertex_coordinates() const {
        std::string str = "[";
        for (int i = 0; i < array.size() - 1; i++) {
            str += "(" + std::to_string(array[i].x) + ", " +
                   std::to_string(array[i].y) + "), ";
        }
        str += "(" + std::to_string(array[array.size() - 1].x) + ", " +
               std::to_string(array[array.size() - 1].y) + ")]";

        return str;
    }

   private:
    struct Vertex {
        float x;
        float y;
    };

    std::vector<Vertex> array;
};

std::ostream &operator<<(std::ostream &os, const Figure &fig) {
    return os << fig.get_vertex_coordinates() << std::endl;
}

std::istream &operator>>(std::istream &is, Figure &fig) {}