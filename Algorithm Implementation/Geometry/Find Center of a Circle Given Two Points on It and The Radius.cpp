/// Given two points on the circle and the radius,
/// Find out the center of the circle if there exist any.

struct Point{
    double x;
    double y;
    Point(){}
    Point(double a,double b){
        x = a;
        y = b;
    }
};

double getDist(Point a,Point b){
    return sqrt(SQ(a.x-b.x) + SQ(a.y-b.y));
}

/// Find the center of the circle which pass through point a & b having radius R.
void findCenter (Point a, Point b, double R) {
    Point g1,g2;
    double x1 = a.x, x2 = b.x;
    double y1 = a.y, y2 = b.y;
    double d = getDist(a, b);
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

int main() {
    double R;
	Point p1,p2;
	cin >> p1.x >> p1.y >> p2.x >> p2.y >> R;
	findCenter(p1,p2,R);
	return 0;
}
