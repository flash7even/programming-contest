#define piii pair<pair<int, int>, int>
#define MP make_pair

/// Returns A,B,C of the equation Ax + By = C.
/// Use the formula (y - y1) = m*(x - x1).
/// m is the slope of this line.

piii findLineEquation(Point P1, Point P2){
	int A = P2.y - P1.y;
	int B = P1.x - P2.x;
	int C = A * P1.x + B * P1.y;
	return MP(MP(A,B), C);
}
