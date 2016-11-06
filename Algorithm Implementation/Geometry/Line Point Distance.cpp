/**
    Give three point A,B,C.Find the distance
    between the point C to the line or line segment AB.
**/

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

struct Point {
	int x, y;
};

double crossProduct(Point A, Point B, Point C) {
	return (B.y - A.y) * (C.x - B.x) - (B.x - A.x) * (C.y - B.y);
}

double dotProduct(Point A, Point B, Point C) {
	return (B.x - A.x) * (C.x - B.x) + (B.y - A.y) * (C.y - B.y);
}

double dist(Point A, Point B) {
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

double linePointDist(Point A, Point B, Point C, bool isSegment) {
	double dis = crossProduct(A, B, C) / dist(A, B);
	if (isSegment) {
		int det1 = dotProduct(A, B, C);
		if (det1 > 0){
			return dist(B, C);
		}
		int det2 = dotProduct(B, A, C);
		if (det2 > 0){
			return dist(A, C);
		}
	}
	return fabs(dis);
}

int main() {
	Point A, B, C;
	bool isSegment;
	/// If isSegment is 0 than it is a line.
	/// Otherwise it is a line segment .
	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> isSegment;
	cout << linePointDist(A, B, C, isSegment) << endl;
	return 0;
}
