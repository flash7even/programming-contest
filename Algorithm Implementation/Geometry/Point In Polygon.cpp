/**
    Check whether a point inside or outside on a polygon.
    A polygon is not a convex hull always.
**/

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;
#define inf 100000

struct Point {
	int x, y;
};

vector<Point> List;
int orientation(Point P, Point Q, Point R) {
	int res = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
	if (res > 0) return 1;
	else if (res < 0) return 2;
	else return 0;
}

bool onSegment(Point P, Point Q, Point R) {
	if (R.x >= min(P.x, Q.x) && R.x <= max(P.x, Q.x) && R.y >= min(P.y, Q.y)
			&& R.y <= max(P.y, Q.y)){
		return true;
	} else {
		return false;
	}
}

bool doIntersect(Point x1, Point y1, Point x2, Point y2, bool &onLine) {
	int o1 = orientation(x1, y1, x2);
	int o2 = orientation(x1, y1, y2);
	int o3 = orientation(x2, y2, x1);
	int o4 = orientation(x2, y2, y1);

	if (o1 != o2 && o3 != o4 && o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0){
		return true;
	}

	if (o1 == 0 && onSegment(x1, y1, x2)) {
		onLine = true;
		return true;
	}

	if (o2 == 0 && onSegment(x1, y1, y2)) return true;
	if (o3 == 0 && onSegment(x2, y2, x1)) return true;
	if (o4 == 0 && onSegment(x2, y2, y1)) return true;
	return false;
}

bool isInside(Point P) {
	Point Q;
	Q.y = P.y + inf;
	Q.x = P.x + inf + 1;
	bool onLine = false;
	int cnt = 0;
	for (int i = 0; i + 1 < List.size(); i++){
		if (doIntersect(List[i], List[i + 1], P, Q, onLine)) cnt++;
	}
	if (onLine) return true;
	if (cnt % 2 == 1) return true;
	return false;
}

int main() {
	/// Number of points of a polygon .
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		Point obj;
		scanf("%d%d", &obj.x, &obj.y);
		List.push_back(obj);
	}
	List.push_back(List[0]);
	/// Check the point whether it is inside or outside on the polygon .

	Point obj;
	scanf("%d%d", &obj.x, &obj.y);
	if (isInside(obj)){
		printf("Yes");
	} else {
		printf("No");
	}
	return 0;
}
