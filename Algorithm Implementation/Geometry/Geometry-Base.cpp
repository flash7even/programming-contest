/// Geometry Base Template
/// Include necessary functions from here to use in other codes
/// If coordinates are double, change accordingly

struct Point {
    LL x, y;
    Point(){}
    Point(LL a, LL b){
        x = a, y = b;
    }
    Point operator - (const Point &t) const{
        Point res;
        res.x = x - t.x;
        res.y = y - t.y;
        return res;
    }
};

LL sqrDist(Point P, Point Q) {
    return (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
}

double dist(Point P, Point Q) {
    double res = (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
    return sqrt(res);
}

/// 0 = Collinear, 1 = Clockwise, 2 = Counterclockwise.
int orientation(Point P, Point Q, Point R) {
    LL ret = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
    if (ret > 0) return 1; /// Polar angle of (Q - R) is smaller than (P - Q) with respect to x axis.
    if (ret < 0) return 2; /// Polar angle of (Q - R) is greater than (P - Q) with respect to x axis.
    return 0; /// Co linear
}

double polygonArea(vector<Point> polygon) {
    double area = 0;
    for (int i = 1; i + 1 < polygon.size(); i++){
        area += (polygon[i].y - polygon[0].y) * (polygon[i + 1].x - polygon[i].x)
                - (polygon[i].x - polygon[0].x) * (polygon[i + 1].y - polygon[i].y);
    }
    return FABS(area / 2.0);
}

/// Compute A X B:
int crossAB(Point A, Point B){
    return (A.x * B.y - A.y * B.x);
}

/// Compute A dot B:
int dotAB(Point A, Point B){
    return (A.x * B.x + A.y * B.y);
}

///Compute the cross product AB X AC
int crossABC(Point A, Point B, Point C) {
    Point AB = Point(B.x - A.x, B.y - A.y); /// AB vector
    Point AC = Point(C.x - A.x, C.y - A.y); /// AC vector
    return crossAB(AB, AC);
}

///Compute the dot product AB dot BC
int dotABC(Point A, Point B, Point C) {
    Point AB = Point(B.x - A.x, B.y - A.y); /// AB vector
    Point BC = Point(C.x - B.x, C.y - B.y); /// BC vector
    return dotAB(AB, BC);
}

/// The angle between two vectors:
double angle(Point A, Point B){
    double ans = fabs((atan2(A.y, A.x) - atan2(B.y, B.x)));
    return ans > pi+eps ? 2*pi-ans : ans;
}

/// Returns angle from positive X
double angelFromAxis(Point P){
    double ang = atan2(P.y, P.x);
    if(ang+eps<0.0) ang += 2.0*pi;
    return ang;
}
