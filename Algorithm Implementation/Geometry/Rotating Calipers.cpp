/**
Some Notes:

1. The antipodal point of a point on the surface of a sphere is
the point which is diametrically opposite to it such that
a line drawn from the one to the other passes through the center
of the sphere and forms a true diameter.

2. Using rotating calipers we can find the distance of all those
antipodal pairs. The maximum one from them is basically the
diameter of the polygon.

3. The method is so named because the idea is analogous to rotating
a spring-loaded vernier caliper around the outside of a convex polygon.
Every time one blade of the caliper lies flat against an edge
of the polygon, it forms an antipodal pair with the point or edge
touching the opposite blade. The complete "rotation" of the caliper
around the polygon detects all antipodal pairs. The set of all pairs,
viewed as a graph, forms a thrackle. The method of rotating calipers
can be interpreted as the projective dual of a sweep line algorithm
in which the sweep is across slopes of lines rather than across
x or y coordinates of points.

**/

/// APPLICATION: FIND MINIMUM WIDTH OF A CONVEX POLYGON(pseudocode):

void findMinimumWidth(){
     ARRAY points := {P1, P2, ..., PN};

     points.delete(middle vertices of any collinear sequence of three points);

     REAL p_a := index of vertex with minimum y-coordinate;
     REAL p_b := index of vertex with maximum y-coordinate;

     REAL rotated_angle := 0;
     REAL min_width := INFINITY;

     VECTOR caliper_a(1,0);    /// Caliper A points along the positive x-axis
     VECTOR caliper_b(-1,0);   /// Caliper B points along the negative x-axis

     WHILE rotated_angle < PI

       /// Determine the angle between each caliper and the next adjacent edge in the polygon
       VECTOR edge_a(points[p_a + 1].x - points[p_a].x, points[p_a + 1].y - points[p_a].y);
       VECTOR edge_b(points[p_b + 1].x - points[p_b].x, points[p_b + 1].y - points[p_b].y);
       REAL angle_a := angle(edge_a, caliper_a);
       REAL angle_b := angle(edge_b, caliper_b);
       REAL width := 0;

       /// Rotate the calipers by the smaller of these angles
       caliper_a.rotate(min(angle_a, angle_b));
       caliper_b.rotate(min(angle_a, angle_b));

       IF angle_a < angle_b
         p_a++;  /// This index should wrap around to the beginning of the array once it hits the end
         width = caliper_a.distance(points[p_b]);
       ELSE
         p_b++;  /// This index should wrap around to the beginning of the array once it hits the end
         width = caliper_b.distance(points[p_a]);
       END IF

       rotated_angle = rotated_angle + min(angle_a, angle_b);

       IF (width < min_width)
         min_width = width;

       END IF
     END WHILE

     RETURN min_width;
}

struct Point{
    double x;
    double y;
};

double area(const Point &a, const Point &b, const Point &c) {
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
    while (area(hull[N - 1], hull[0], hull[(k + 1) % N]) >
            area(hull[N - 1], hull[0], hull[k])){
        ++k;
    }
    double res = 0;
    for (int i = 0, j = k; i <= k && j < N; i++) {
        res = max(res, dist(hull[i], hull[j]));
        while (j < N && area(hull[i], hull[(i + 1) % N], hull[(j + 1) % N]) >
                area(hull[i], hull[(i + 1) % N], hull[j])) {
            res = max(res, dist(hull[i], hull[(j + 1) % N]));
            ++j;
        }
    }
    return res;
}
