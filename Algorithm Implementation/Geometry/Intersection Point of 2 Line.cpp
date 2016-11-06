/**
    Line Line Intersection .
    Give two lines . Find their intersect point.
 **/

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

struct Point {
	int x, y;
};

double polygonArea(vector<Point> list) {
	double area = 0;
	for (int i = 1; i + 1 < list.size(); i++) {
		area += (list[i].y - list[0].y) * (list[i + 1].x - list[i].x)
				- (list[i].x - list[0].x) * (list[i + 1].y - list[i].y);
	}
	return fabs(area / 2.0);
}

/// P1 and P2 are end points of line 1 and P3 and P4 are end point of line 2.
Point P1, P2, P3, P4;

void findIntersectionPoint() {
	/// A1*x + B1*y = C1
	double A1 = P2.y - P1.y, B1 = P1.x - P2.x, C1 = A1 * P1.x + B1 * P1.y;
	/// A2*x + B2*y = C2
	double A2 = P4.y - P3.y, B2 = P3.x - P4.x, C2 = A2 * P3.x + B2 * P3.y;
	/// Find determinant
	double det = A1 * B2 - A2 * B1;
	/// If determinant is zero the lines never intersect.
	/// Then they can be either collinear or parallel.
	if (det == 0) {
		vector<Point> list;
		list.push_back(P1);
		list.push_back(P3);
		list.push_back(P4);
		list.push_back(P2);
		if (polygonArea(list) == 0) {
			printf("Collinear\n");
		} else {
			printf("Parallel\n");
		}
	} else {
		double x = (B2 * C1 - B1 * C2) / det;
		double y = (A1 * C2 - A2 * C1) / det;
		printf("%.2lf %.2lf\n", x, y);
	}
}

int main() {
	cin >> P1.x >> P1.y >> P2.x >> P2.y >> P3.x >> P3.y >> P4.x >> P4.y;
	findIntersectionPoint();
	return 0;
}
