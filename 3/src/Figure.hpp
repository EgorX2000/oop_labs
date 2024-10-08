#pragma once

#include <iostream>
#include <sstream>
#include <vector>

class Figure {
   private:
    struct Vertex {
        float x;
        float y;
    };

    std::vector<Vertex> array;

   public:
    virtual Vertex get_geometric_center();

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

    void enter_figure_information(const std::string &str) {
        std::istringstream str_ss(str);

        float num;
        size_t i = 0;
        while (str_ss >> num) {
            Vertex ver{0, 0};
            if (i % 2 == 0) {
                ver.x = num;
            } else {
                ver.y = num;
            }

            array.push_back(ver);
            i++;
        }
    }

    virtual double area() = 0;
};

std::ostream &operator<<(std::ostream &os, const Figure &fig) {
    return os << fig.get_vertex_coordinates() << std::endl;
}

std::istream &operator>>(std::istream &is, Figure &fig) {}