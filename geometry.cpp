#include "geometry.h"
#include <algorithm>
#include <cmath>


// Helper function to check if two bounding boxes intersect
bool boundingBoxesIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    double minX1 = std::min(p1.x, q1.x);
    double maxX1 = std::max(p1.x, q1.x);
    double minY1 = std::min(p1.y, q1.y);
    double maxY1 = std::max(p1.y, q1.y);

    double minX2 = std::min(p2.x, q2.x);
    double maxX2 = std::max(p2.x, q2.x);
    double minY2 = std::min(p2.y, q2.y);
    double maxY2 = std::max(p2.y, q2.y);

    return (minX1 <= maxX2 && maxX1 >= minX2 && minY1 <= maxY2 && maxY1 >= minY2);
}

// Helper function to check if a point lies on a line segment
bool onSegment(const Point& p, const Point& q, const Point& r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

// Function to calculate distance between two points
double distance(const Point& p1, const Point& p2) {
    return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// Updated orientation function with epsilon for precision handling
int orientation(const Point& p, const Point& q, const Point& r, double epsilon) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (std::fabs(val) < epsilon) return 0;  // Collinear
    return (val > 0) ? 1 : 2;  // 1 -> Clockwise, 2 -> Counterclockwise
}

// Function to check if two line segments intersect
bool doIntersect(const Line& l1, const Line& l2){
    Point p1 = l1.p1, q1 = l1.p2;
    Point p2 = l2.p1, q2 = l2.p2;

    // Bounding box check for quick exclusion
    if (!boundingBoxesIntersect(p1, q1, p2, q2)) return false;

    // Find orientations
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: If orientations are different, they intersect
    if(o1 != o2 && o3 != o4) return true;

    // Special cases (collinear points)
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Otherwise, no intersection
}

// Check if two circles intersect
bool doIntersect(const Circle& c1, const Circle& c2) {
    double d = distance(c1.center, c2.center);
    return d <= (c1.radius + c2.radius) && d >= std::abs(c1.radius - c2.radius);
}

// Check if a line intersects a circle
bool doIntersect(const Line& l, const Circle& c) {
    // Calculate the distance from the circle's center to the line
    double a = l.p2.y - l.p1.y;
    double b = l.p1.x - l.p2.x;
    double c_val = a * l.p1.x + b * l.p1.y;

    double distanceToLine = std::abs(a * c.center.x + b * c.center.y - c_val) / std::sqrt(a * a + b * b);
    return distanceToLine <= c.radius;
}

// Check if two polygons intersect
bool doIntersect(const Polygon& poly1, const Polygon& poly2) {
    // Check if any edge of poly1 intersects with any edge of poly2
    for (size_t i = 0; i < poly1.vertices.size(); i++) {
        Point p1 = poly1.vertices[i];
        Point q1 = poly1.vertices[(i + 1) % poly1.vertices.size()];

        for (size_t j = 0; j < poly2.vertices.size(); j++) {
            Point p2 = poly2.vertices[j];
            Point q2 = poly2.vertices[(j + 1) % poly2.vertices.size()];

            if (doIntersect(Line(p1, q1), Line(p2, q2))) {
                return true;
            }
        }
    }

    return false;
}