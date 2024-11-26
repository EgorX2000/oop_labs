#include <math.h>

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template <class T>
concept scalar = std::is_scalar_v<T>;

template <scalar T>
struct Vertex {
    Vertex() = default;
    Vertex(T x_in, T y_in) : x(x_in), y(y_in) {}

    Vertex operator+(const Vertex& vert) const {
        return Vertex(x + vert.x, y + vert.y);
    }
    Vertex operator-(const Vertex& vert) const {
        return Vertex(x - vert.x, y - vert.y);
    }
    Vertex& operator+=(const Vertex& vert) {
        x += vert.x;
        y += vert.y;

        return *this;
    }
    Vertex& operator-=(const Vertex& vert) {
        x -= vert.x;
        y -= vert.y;

        return *this;
    }
    bool operator==(const Vertex& vert) const {
        return x == vert.x && y == vert.y;
    }
    bool operator!=(const Vertex& vert) const { return !(*this == vert); }
    friend std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) {
        os << "(" << vertex.x << ", " << vertex.y << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Vertex<T>& vertex) {
        is >> vertex.x >> vertex.y;
        return is;
    }

   public:
    T x = 0;
    T y = 0;
};

template <scalar T>
class Figure {
   public:
    virtual Vertex<T> GetCenter() const = 0;
    virtual double GetArea() const = 0;
    virtual operator double() const = 0;
};

template <scalar T>
class Polygon : public Figure<T> {
   protected:
    Polygon(const std::string& name, const std::vector<Vertex<T>>& verts)
        : figName(name), vertices(verts) {}

   public:
    friend std::ostream& operator<<(std::ostream& os,
                                    const Polygon<T>& figure) {
        os << figure.GetName() << ": " << " { ";
        for (auto& v : figure.vertices) {
            os << v;
        }
        os << "}";

        return os;
    }
    virtual inline std::string GetName() const { return figName; }
    virtual inline std::vector<Vertex<T>> GetVertices() const {
        return vertices;
    }
    bool operator==(const Polygon<T>& obj) const {
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
    virtual ~Polygon() = default;

   protected:
    std::string figName;
    std::vector<Vertex<T>> vertices;
};

template <scalar T>
class Octagon : public Polygon<T> {
   public:
    Octagon(const Vertex<T>& pos, T sideLen)
        : pos(pos),
          sideLen(sideLen),
          Polygon<T>("Octagon", MakeVertices(pos, sideLen)) {}
    Vertex<T> GetCenter() const override {
        double centerX =
            (this->vertices[0].x + this->vertices[1].x + this->vertices[2].x +
             this->vertices[3].x + this->vertices[4].x + this->vertices[5].x +
             this->vertices[6].x + this->vertices[7].x) /
            8;
        double centerY =
            (this->vertices[0].y + this->vertices[1].y + this->vertices[2].y +
             this->vertices[3].y + this->vertices[4].y + this->vertices[5].y +
             this->vertices[6].y + this->vertices[7].y) /
            8;

        return Vertex<T>{centerX, centerY};
    }
    double GetArea() const override {
        return 2 * (1 + sqrt(2)) * pow(sideLen, 2);
    }
    operator double() const override { return GetArea(); }
    bool operator==(const Octagon& obj) const {
        for (int i = 0, j = 0; j < 8; j++) {
            if (i == 8) {
                return true;
            } else if (this->vertices[i] == obj.vertices[j]) {
                i++;
                j = -1;
            }
        }
        return false;
    }

    friend std::istream& operator>>(std::istream& is, Octagon& obj) {
        is >> obj.pos;
        is >> obj.sideLen;

        return is;
    }

   private:
    static std::vector<Vertex<T>> MakeVertices(const Vertex<T>& v, T sideLen) {
        std::vector<Vertex<T>> vertices;

        vertices.push_back(v);
        vertices.push_back({v.x, v.y + sideLen});
        vertices.push_back({v.x + sideLen * cos(M_PI / 4),
                            v.y + sideLen + sideLen * sin(M_PI / 4)});
        vertices.push_back({v.x + sideLen * cos(M_PI / 4) + sideLen,
                            v.y + sideLen + sideLen * sin(M_PI / 4)});
        vertices.push_back(
            {v.x + sideLen * cos(M_PI / 4) + sideLen + sideLen * cos(M_PI / 4),
             v.y + sideLen});
        vertices.push_back(
            {v.x + sideLen * cos(M_PI / 4) + sideLen + sideLen * cos(M_PI / 4),
             v.y});
        vertices.push_back({v.x + sideLen * cos(M_PI / 4) + sideLen,
                            v.y - sideLen * sin(M_PI / 4)});
        vertices.push_back(
            {v.x + sideLen * cos(M_PI / 4), v.y - sideLen * sin(M_PI / 4)});

        return vertices;
    }

   private:
    Vertex<T> pos;
    T sideLen;
};

template <scalar T>
class Triangle : public Polygon<T> {
   public:
    Triangle(const Vertex<T>& pos, T sideLen)
        : pos(pos),
          sideLen(sideLen),
          Polygon<T>("Triangle", MakeVertices(pos, sideLen)) {}
    Vertex<T> GetCenter() const override {
        double centerX =
            (this->vertices[0].x + this->vertices[1].x + this->vertices[2].x) /
            3;
        double centerY =
            (this->vertices[0].y + this->vertices[1].y + this->vertices[2].y) /
            3;

        return Vertex<T>{centerX, centerY};
    }
    double GetArea() const override { return sqrt(3) / 4 * pow(sideLen, 2); }
    operator double() const override { return GetArea(); }
    bool operator==(const Triangle& obj) const {
        for (int i = 0, j = 0; j < 3; j++) {
            if (i == 3) {
                return true;
            } else if (this->vertices[i] == obj.vertices[j]) {
                i++;
                j = -1;
            }
        }
        return false;
    }

    friend std::istream& operator>>(std::istream& is, Triangle& obj) {
        std::vector<Vertex<T>> vertices;

        is >> obj.pos;
        is >> obj.sideLen;

        return is;
    }

   private:
    static std::vector<Vertex<T>> MakeVertices(const Vertex<T>& v, T sideLen) {
        std::vector<Vertex<T>> vertices;

        vertices.push_back(v);
        vertices.push_back(
            {v.x + sideLen * cos(M_PI / 3), v.y + sideLen * sin(M_PI / 3)});
        vertices.push_back({v.x + sideLen, v.y});

        return vertices;
    }

   private:
    Vertex<T> pos;
    T sideLen;
};

template <scalar T>
class Square : public Polygon<T> {
   public:
    Square(const Vertex<T>& pos, T sideLen)
        : pos(pos),
          sideLen(sideLen),
          Polygon<T>("Square", MakeVertices(pos, sideLen)) {}
    Vertex<T> GetCenter() const override {
        return Vertex<T>{pos.x + sideLen * 0.5, pos.y + sideLen * 0.5};
    }
    double GetArea() const override { return pow(sideLen, 2); }
    operator double() const override { return GetArea(); }
    bool operator==(const Square& obj) const {
        return sideLen == obj.sideLen && pos == obj.pos;
    }
    friend std::istream& operator>>(std::istream& is, Square& obj) {
        is >> obj.pos;
        is >> obj.sideLen;

        return is;
    }

   private:
    static std::vector<Vertex<T>> MakeVertices(const Vertex<T>& v, T sideLen) {
        std::vector<Vertex<T>> vertices;

        vertices.push_back(v);
        vertices.push_back({v.x + sideLen, v.y});
        vertices.push_back({v.x, v.y + sideLen});
        vertices.push_back({v.x + sideLen, v.y + sideLen});

        return vertices;
    }

   private:
    Vertex<T> pos;
    T sideLen;
};