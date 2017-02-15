struct Point{
    double x,y;
};

/// 0 --> Collinear
/// 1 --> Clockwise
/// 2 --> Counterclockwise

int orientation(Point P, Point Q, Point R) {
	LL ret = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
	if (ret > 0) return 1; /// Polar angle of (Q - R) is smaller than (P - Q) with respect to x axis.
	if (ret < 0) return 2; /// Polar angle of (Q - R) is greater than (P - Q) with respect to x axis.
	return 0; /// Co linear
}
