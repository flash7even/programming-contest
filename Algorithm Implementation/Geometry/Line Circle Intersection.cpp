/// Find the intersection points of a line and a circle.
/// Source: http://math.stackexchange.com/questions/311921/get-location-of-vector-circle-intersection

struct Point{
    double x;
    double y;
};

pair<Point,Point> Line_Circle_Intersection(Point center, double r, Point P1, Point P2){
    double a1 = P2.x - P1.x;
    double a2 = P2.y - P1.y;
    double b1 = P1.x - center.x;
    double b2 = P1.y - center.y;

    /// At^2 + Bt + C = 0:
    double A = SQ(a1) + SQ(a2);
    double B = (a1*b1 + a2*b2)*2;
    double C = SQ(b1) + SQ(b2) - SQ(r);

    if((B*B - 4.0*A*C)<0){
        /// Does not intersect.
    }else if((B*B - 4.0*A*C) == 0){
        /// The line is tangent with the circle at a single point.
    }else{
        /// The line intersect the circle at two points.
        double t1 = (-B - sqrt(B*B - 4.0*A*C))/2.0/A;
        double t2 = (-B + sqrt(B*B - 4.0*A*C))/2.0/A;

        Point E1 = {P1.x + a1*t1, P1.y + a2*t1};
        Point E2 = {P1.x + a1*t2, P1.y + a2*t2};
        return MP(E1,E2);
    }
}
