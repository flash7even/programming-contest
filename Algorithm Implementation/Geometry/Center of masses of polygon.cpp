/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

class Point {
public:
    double x, y;
    Point () {
        x = 0;
        y = 0;
    }
    Point (double tx, double ty) {
        x = tx;
        y = ty;
    }
    bool operator <(const Point &p) const {
        return x < p.x || x == p.x && y < p.y;
    }
};

inline double cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P) {
    int n = P.size(), k = 0;
    vector<Point> H(2 * n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) { // The point with index n - 1 is already in H
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k - 1);
    return H;
}

double polygon_area (vector<Point> P) {
    double area = 0;
    int sz = P.size();
    for (int i = 0; i < sz; ++i) {
        Point cur = P[i];
        Point next = P[(i + 1) % sz];
        area += (cur.x * next.y - cur.y * next.x);
    }
    return area/2.0;
}

/// Given a convex hull it returns the center of masses or gravity
/// of that convex polygon.

Point center_of_mass (vector<Point> P) {
    double area = polygon_area(P);
    double cx = 0, cy = 0;
    int sz = P.size();
    for (int i = 0; i < sz; ++i) {
        Point cur = P[i];
        Point next = P[(i + 1) % sz];
        cx += (cur.x + next.x) * (cur.x * next.y - cur.y * next.x);
        cy += (cur.y + next.y) * (cur.x * next.y - cur.y * next.x);
    }
    cx = cx/(6.0 * area);
    cy = cy/(6.0 * area);
    return Point(cx, cy);
}

vector<Point> hull;

int main() {
    int n;
    while(sf("%d", &n)) {
        if (n < 3)  break;
        hull.clear();
        for (int i = 0, x, y; i < n; ++i) {
            sf("%d %d", &x, &y);
            hull.push_back(Point(x, y));
        }
        hull = convex_hull(hull);
        Point center = center_of_mass(hull);
        printf("%.3lf %.3lf\n", center.x, center.y);
    }
}
