/// Tangent Line Between Circles

/**
    Finds tangent segments between two given circles.

    Returns an empty, or 2x1, or 4x1 list of segments representing
    the two exterior and two interior tangent segments (in that order).
    If some tangents don't exist, they aren't present in the res.
    Each segment is represented by the two end points.

    Exterior tangents exist if one of the circles doesn't contain
    the other. Interior tangents exist if circles don't intersect.

    In the limiting case when circles touch from outside/inside, there are
    no interior/exterior tangents, respectively, but just one common
    tangent line (which isn't returned at all, or returned as two very
    close or equal points by this code, depending on roundoff -- sorry!)

    Note: If you need the tangent from a point to a circle,
    just make the radius of one circle zero(it becomes a point then).
**/

struct Point{
    double x, y;
};

struct tangent{
    Point p1, p2;
};

/// Parameters: Center and radius of two circles
vector<tangent> findTangentLine(double x1, double y1, double r1, double x2, double y2, double r2){
    vector<tangent> res;

    double sqDist = SQ(x1 - x2) + SQ(y1 - y2);
    if (sqDist <= SQ(r1-r2)){
        /// No tangent point.
        return res;
    }

    double d = sqrt(sqDist);
    double vx = (x2 - x1) / d;
    double vy = (y2 - y1) / d;

    for(int sign1 = +1; sign1 >= -1; sign1 -= 2) {
        double c = (r1 - sign1 * r2) / d;

        /// Now we're just intersecting a line with a circle: v*n=c, n*n=1

        if (c*c > 1.0) continue;
        double h = sqrt(max(0.0, 1.0 - c*c));

        for (int sign2 = +1; sign2 >= -1; sign2 -= 2) {
            double nx = vx * c - sign2 * h * vy;
            double ny = vy * c + sign2 * h * vx;

            tangent t;
            t.p1.x = x1 + r1 * nx;
            t.p1.y = y1 + r1 * ny;
            t.p2.x = x2 + sign1 * r2 * nx;
            t.p2.y = y2 + sign1 * r2 * ny;
            res.pb(t);
        }
    }
    return res;
}
