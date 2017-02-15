/// Given a line segment and a point find minimum distance between them.
/// Driver function: linePointDist().
/// Complexity: O(1).

struct Point {
	int x, y;
};

/// Compute A X B:
int cross(Point A, Point B){
    return (A.x * B.y - A.y * B.x);
}

/// Compute A dot B:
int dot(Point A, Point B){
    return (A.x * B.x + A.y * B.y);
}

///Compute the cross product AB X AC
int crossProduct(Point A, Point B, Point C) {
    Point AB = {B.x - A.x, B.y - A.y}; /// AB vector
    Point AC = {C.x - A.x, C.y - A.y}; /// AC vector
    return cross(AB, AC);
}

///Compute the dot product AB dot BC
int dotProduct(Point A, Point B, Point C) {
    Point AB = {B.x - A.x, B.y - A.y}; /// AB vector
    Point BC = {C.x - B.x, C.y - B.y}; /// BC vector
    return dot(AB, BC);
}

double dist(Point A, Point B) {
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

/// Find the minimum distance between C and line/segment (A - B):
/// isSegment = true if (A - B) is a segment.

double linePointDist(Point A, Point B, Point C, bool isSegment) {
	double d = (double)crossProduct(A, B, C) / dist(A, B);
	if (isSegment) {
		if (dotProduct(A, B, C) > 0) return dist(B, C);
		if (dotProduct(B, A, C) > 0) return dist(A, C);
	}
	return fabs(d);
}
