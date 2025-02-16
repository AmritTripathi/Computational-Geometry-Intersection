#include <iostream>
#include "geometry.h"

void testIntersection(Point p1, Point q1, Point p2, Point q2) {
    Line l1(p1, q1);
    Line l2(p2, q2);

    if (doIntersect(l1, l2)) {
        std::cout << "The lines intersect!" << std::endl;
    } else {
        std::cout << "The lines do not intersect." << std::endl;
    }
}

int main() {
    // Test Circle-Circle intersection
    Circle c1(Point(0, 0), 5);
    Circle c2(Point(3, 4), 5);
    if (doIntersect(c1, c2)) {
        std::cout << "The circles intersect!" << std::endl;
    } else {
        std::cout << "The circles do not intersect." << std::endl;
    }

    // Test Line-Circle intersection
    Line l(Point(-10, 0), Point(10, 0));
    Circle c3(Point(0, 0), 3);
    if (doIntersect(l, c3)) {
        std::cout << "The line intersects the circle!" << std::endl;
    } else {
        std::cout << "The line does not intersect the circle." << std::endl;
    }

    // Test Polygon-Polygon intersection
    Polygon poly1({Point(0, 0), Point(4, 0), Point(4, 4), Point(0, 4)});
    Polygon poly2({Point(2, 2), Point(6, 2), Point(6, 6), Point(2, 6)});
    if (doIntersect(poly1, poly2)) {
        std::cout << "The polygons intersect!" << std::endl;
    } else {
        std::cout << "The polygons do not intersect." << std::endl;
    }
}

// Potential Improvements/Edge Cases (Optional):
// Collinear Points: Properly handle edge cases for line intersection, such as collinear and overlapping line segments.
// Circle-Tangent Intersection: Address scenarios where the circle just touches the line or another circle (tangential intersection).
// Polygon Self-Intersection: If the polygons are not simple, self-intersecting edges could complicate intersection checks.
// Convex vs. Concave Polygons: Optimizations for convex polygons can improve performance.
// Edge Intersection Precision: Depending on your requirements, floating-point precision issues could cause errors, so epsilon-based comparisons may be needed.