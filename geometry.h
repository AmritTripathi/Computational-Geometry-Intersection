#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

struct Point {
    double x;
    double y;

    Point(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}
};

struct Line {
    Point p1;
    Point p2;

    Line(Point point1, Point point2) : p1(point1), p2(point2) {}
};

struct Circle {
    Point center;
    double radius;

    Circle(Point c, double r) : center(c), radius(r) {}
};

struct Polygon {
    std::vector<Point> vertices;

    Polygon(std::vector<Point> points) : vertices(points) {}
};

// Funcion declarations
int orientation(const Point& p, const Point& q, const Point& r, double epsilon = 1e-9);    
bool onSegment(const Point& p, const Point& q, const Point& r);

bool doIntersect(const Line& l1, const Line& l2);               // Line-Line intersection
bool doIntersect(const Circle& c1, const Circle& c2);           // Circle-Circle intersection
bool doIntersect(const Line& l, const Circle& c);               // Line-Circle intersection
bool doIntersect(const Polygon& poly1, const Polygon& poly2);   // Polygon-Polygon intersection
#endif // GEOMETRY_H