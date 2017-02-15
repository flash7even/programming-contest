/// Check whether a point lie inside a polygon.
/// The polygon can be concave or convex.
/// Driver function: isInside().
/// Complexity: O(N).

#define inf 100000

struct Point {
	int x, y;
};

vector<Point> List; /// Points in the polygon

int orientation(Point P, Point Q, Point R){
	int res = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
	if (res > 0) return 1;
	else if (res < 0) return 2;
	else return 0;
}

bool onSegment(Point P, Point Q, Point R){
	if (R.x >= min(P.x, Q.x) && R.x <= max(P.x, Q.x) && R.y >= min(P.y, Q.y)
			&& R.y <= max(P.y, Q.y)){
		return true;
	}else{
		return false;
	}
}

bool doIntersect(Point P1, Point P2, Point P3, Point P4, bool &onLine){
	int o1 = orientation(P1, P2, P3);
	int o2 = orientation(P1, P2, P4);
	int o3 = orientation(P3, P4, P1);
	int o4 = orientation(P3, P4, P2);

	if (o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0){
		return true;
	}

	if (o1 == 0 && onSegment(P1, P2, P3)){
		onLine = true;
		return true;
	}

	if (o2 == 0 && onSegment(P1, P2, P4)) return true;
	if (o3 == 0 && onSegment(P3, P4, P1)) return true;
	if (o4 == 0 && onSegment(P3, P4, P2)) return true;
	return false;
}

bool isInside(Point P) {
	Point Q;
	Q.y = P.y + inf;
	Q.x = P.x + inf + 1;
	bool onLine = false; /// To check if the point lie on any segment
	int cnt = 0;
	for (int i = 0; i + 1 < List.size(); i++){
		if (doIntersect(List[i], List[i + 1], P, Q, onLine)) cnt++;
	}
	if (onLine) return true;
	if (cnt % 2 == 1) return true;
	return false;
}
