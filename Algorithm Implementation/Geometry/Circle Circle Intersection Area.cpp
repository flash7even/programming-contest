/// Given two circle, find the intersected area between them.
/// Link: http://mathforum.org/library/drmath/view/54785.html

struct Point{
	double x,y;
};

double dist(Point a, Point b) {
    return sqrt(SQ((a.x-b.x)) + SQ((a.y-b.y)));
}

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
