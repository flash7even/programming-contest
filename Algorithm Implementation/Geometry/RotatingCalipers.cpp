/// Rotating Calipers

/**
Some Notes:
1. The antipodal point of a point on the surface of a sphere is
the point which is diametrically opposite to it such that
a line drawn from the one to the other passes through the center
of the sphere and forms a true diameter.
2. Using rotating calipers we can find the distance of all those
antipodal pairs. The maximum one from them is basically the
diameter of the polygon.
**/

struct Point{
    double x;
    double y;
};

double triArea(const Point &a, const Point &b, const Point &c) {
    return abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

double dist(const Point &a, const Point &b) {
    return sqrt(SQ(a.x - b.x) + SQ(a.y - b.y));
}

/// Find the diameter of a polygon:
double diameter(const vector<Point> &List) {
    vector<Point> hull = convexHull(List);
    int N = hull.size();
    if (N == 1) return 0;
    if (N == 2) return dist(hull[0], hull[1]);
    int k = 1;
    while (triArea(hull[N - 1], hull[0], hull[(k + 1) % N]) >
            triArea(hull[N - 1], hull[0], hull[k])){
        ++k;
    }
    double res = 0;
    for (int i = 0, j = k; i <= k && j < N; i++) {
        res = max(res, dist(hull[i], hull[j]));
        while (j < N && triArea(hull[i], hull[(i + 1) % N], hull[(j + 1) % N]) >
                triArea(hull[i], hull[(i + 1) % N], hull[j])) {
            res = max(res, dist(hull[i], hull[(j + 1) % N]));
            ++j;
        }
    }
    return res;
}
