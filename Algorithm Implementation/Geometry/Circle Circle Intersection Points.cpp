/// Given two circles, find the intersection points between them.
/// Source: http://paulbourke.net/geometry/circlesphere/

struct Point{
	double x,y;
};

double Dist(Point a, Point b){
    return sqrt(SQ(a.x - b.x) + SQ(a.y - b.y));
}

pair<Point,Point> circleCircleIntersectionPoints(Point P0, double R0, Point P1, double R1) {
	double d = Dist(P0, P1);

	if(d > R0 + R1){
        /// They don't intersect.
	}else if(d < FABS(R0 - R1)){
        /// One fully contains the other one.
	}else if(FABS(d - 0)<eps && R0 == R1){
        /// Both are same circle.
	}

	/// Otherwise the circles intersect with each other.

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

	return MP(E1, E2);
}
