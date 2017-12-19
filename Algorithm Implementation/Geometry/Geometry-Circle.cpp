/// Circle Geometry
/// Use necessary functions related to circle
/// Don't forget to include base template

struct circleGeometry{

    /// Find the intersection points of a line and a circle
    /// Parameters: Circle center, radius, line end points P1 and P2
    pair<Point,Point> lineCircleIntersectionPoints(Point center, double r, Point P1, Point P2){
        double a1 = P2.x - P1.x;
        double a2 = P2.y - P1.y;
        double b1 = P1.x - center.x;
        double b2 = P1.y - center.y;

        // At^2 + Bt + C = 0
        double A = SQ(a1) + SQ(a2);
        double B = (a1*b1 + a2*b2)*2;
        double C = SQ(b1) + SQ(b2) - SQ(r);

        if((B*B - 4.0*A*C)<0){
            /// Does not intersect
        }else if((B*B - 4.0*A*C) == 0){
            /// The line is tangent with the circle at a single point
        }else{
            /// The line intersect the circle at two points
            double t1 = (-B - sqrt(B*B - 4.0*A*C))/2.0/A;
            double t2 = (-B + sqrt(B*B - 4.0*A*C))/2.0/A;

            Point E1 = {P1.x + a1*t1, P1.y + a2*t1};
            Point E2 = {P1.x + a1*t2, P1.y + a2*t2};
            return MP(E1,E2);
        }
    }

    /// Find intersected area of two circles
    /// Parameters: 1st circle center, radius, 2nd circle center, radius
    double circleCircleIntersectionArea(Point P0, double R0, Point P1, double R1) {
        double d = dist(P0, P1);
        if(R0 + R1 <= d) return 0;
        if(R0 >= R1 && (R0 - R1) >= d) return pi * SQ(R1);
        if(R0 <= R1 && (R1 - R0) >= d) return pi * SQ(R0);

        double CAD = 2.0 * acos((SQ(R0) + SQ(d) - SQ(R1)) / (2.0 * R0 * d));
        double CBD = 2.0 * acos((SQ(R1) + SQ(d) - SQ(R0)) / (2.0 * R1 * d));

        //double A1 = (0.5 * SQ(R0) * CAD) - (0.5 * SQ(R0) * sin(CAD));
        double A1 = 0.5 * SQ(R0) * (CAD - sin(CAD));
        //double A2 = (0.5 * SQ(R1) * CBD) - (0.5 * SQ(R1) * sin(CBD));
        double A2 = 0.5 * SQ(R1) * (CBD - sin(CBD));
        return (A1 + A2);
    }

    /// Find intersection points of two circles
    /// Parameters: 1st circle center, radius, 2nd circle center, radius
    void circleCircleIntersectionPoints(Point P0, double R0, Point P1, double R1) {
        double d = dist(P0, P1);

        if(d > R0 + R1){
            /// They don't intersect.

        }else if(d < FABS(R0 - R1)){
            /// One fully contains the other one.

        }else if(FABS(d - 0)<eps && R0 == R1){
            /// Both are same circle.

        }else{
            /// The circles intersect with each other

            double a = (SQ(R0) - SQ(R1) + SQ(d))/(2.0 * d);
            double b = d - a;
            double h = sqrt(SQ(R0) - SQ(a));

            double rx = -(P1.y - P0.y) * (h/d);
            double ry = (P1.x - P0.x) * (h/d);

            Point P2;
            P2.x = P0.x + (a * (P1.x - P0.x))/d;
            P2.y = P0.y + (a * (P1.y - P0.y))/d;

            Point E1 = {P2.x + rx, P2.y + ry};
            Point E2 = {P2.x - rx, P2.y - ry};

            /// E1, E2 are the intersection points. Return if needed.
        }
    }

    /// Find the center of the circle which pass through point a & b having radius R.
    void findCenterGivenTwoPointsOnIt(Point a, Point b, double R) {
        Point g1,g2;
        double x1 = a.x, x2 = b.x;
        double y1 = a.y, y2 = b.y;
        double d = dist(a, b);
        if (d * d > 4.0 * R * R) {
            /// Not Possible to Find any Center;
            return;
        }
        double x_part = sqrt(R * R - 0.25 * d * d) * (y1 - y2) / d;
        double y_part = sqrt(R * R - 0.25 * d * d) * (x2 - x1) / d;
        double x3 = 0.5 * (x1 + x2), y3 = 0.5 * (y1 + y2);
        g1 = Point(x3 + x_part, y3 + y_part); /// One possible center
        g2 = Point(x3 - x_part, y3 - y_part); /// Another possible center
    }

    /// Given 3 points A, B, C on the circumference of a circle
    /// Find the center of that circle
    Point circleCenter(Point A, Point B, Point C) {
        double yDelta_a = B.y - A.y;
        double xDelta_a = B.x - A.x;
        double yDelta_b = C.y - B.y;
        double xDelta_b = C.x - B.x;
        Point center = Point(0.0, 0.0);

        double aSlope = yDelta_a/xDelta_a;
        double bSlope = yDelta_b/xDelta_b;
        center.x = (aSlope*bSlope*(A.y - C.y) + bSlope*(A.x + B.x)
                    - aSlope*(B.x + C.x) )/(2* (bSlope - aSlope));
        center.y = -1*(center.x - (A.x + B.x)/2)/aSlope +  (A.y + B.y)/2;
        return center;
    }

}circleGeo;
