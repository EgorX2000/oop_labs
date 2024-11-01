#pragma once

#include <math.h>

#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    Vertex() = default;
    Vertex(double x_in, double y_in) : x(x_in), y(y_in) {}
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
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
        os << "(" << vertex.x << ", " << vertex.y << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Vertex& vertex) {
        is >> vertex.x >> vertex.y;
        return is;
    }

   public:
    double x = 0;
    double y = 0;
};

class Figure {
   public:
    virtual Vertex GetCenter() const = 0;
    virtual double GetArea() const = 0;
    virtual operator double() const = 0;
};

class Polygon : public Figure {
   protected:
    Polygon(const std::string& name, const std::vector<Vertex>& verts)
        : figName(name), vertices(verts) {}

   public:
    friend std::ostream& operator<<(std::ostream& os, const Polygon& Figure);
    virtual inline std::string GetName() const { return figName; }
    virtual inline std::vector<Vertex> GetVertices() const { return vertices; }
    bool operator==(const Polygon& vert) const;
    virtual ~Polygon() = default;

   protected:
    std::string figName;
    std::vector<Vertex> vertices;
};

class Octagon : public Polygon {
   public:
    Octagon(const Vertex& pos, double sideLen)
        : pos(pos),
          sideLen(sideLen),
          Polygon("Octagon", MakeVertices(pos, sideLen)) {}
    Vertex GetCenter() const override;
    double GetArea() const override;
    operator double() const override;
    bool operator==(const Octagon& vert) const;
    friend std::istream& operator>>(std::istream& is, Octagon& Figure);

   private:
    static std::vector<Vertex> MakeVertices(const Vertex& v, double sideLen);

   private:
    Vertex pos;
    double sideLen;
};

class Triangle : public Polygon {
   public:
    Triangle(const Vertex& pos, double sideLen)
        : pos(pos),
          sideLen(sideLen),
          Polygon("Triangle", MakeVertices(pos, sideLen)) {}
    Vertex GetCenter() const override;
    double GetArea() const override;
    operator double() const override;
    bool operator==(const Triangle& vert) const;
    friend std::istream& operator>>(std::istream& is, Triangle& Figure);

   private:
    static std::vector<Vertex> MakeVertices(const Vertex& v, double sideLen);

   private:
    Vertex pos;
    double sideLen;
};

class Square : public Polygon {
   public:
    Square(const Vertex& pos, double sideLen)
        : pos(pos),
          sideLen(sideLen),
          Polygon("Square", MakeVertices(pos, sideLen)) {}
    Vertex GetCenter() const override;
    double GetArea() const override;
    operator double() const override;
    bool operator==(const Square& vert) const;
    friend std::istream& operator>>(std::istream& is, Square& Figure);

   private:
    static std::vector<Vertex> MakeVertices(const Vertex& v, double sideLen);

   private:
    Vertex pos;
    double sideLen;
};