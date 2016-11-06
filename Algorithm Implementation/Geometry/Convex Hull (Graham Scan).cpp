/*
	Convex Hull Graham Scan algorithm.
	Given a set of N number points.
	Find the smallest convex polygon that contains all the points.
	Time Complexity O(NlogN).
	N is the number of points.
 */

#include <bits/stdc++.h>
#define LL long long
using namespace std;

struct Point {
	LL x, y;
};

Point pointList[110];
Point hullPoints[110];
stack<Point> S;
int N,cnt;

LL dist(Point P, Point Q) {
	return (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
}

LL orientation(Point P, Point Q, Point R) {
	LL ret = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
	if (ret > 0) return 1;
	if (ret < 0) return 2;
	return ret;
}

bool cmp(Point X, Point Y) {
	LL ret = orientation(pointList[0], X, Y);
	if (ret == 0) {
		LL dist1 = dist(pointList[0], X);
		LL dist2 = dist(pointList[0], Y);
		return (dist1 < dist2);
	} else if (ret == 2){
		return true;
	} else {
		return false;
	}
}

Point nextToTop() {
	Point P = S.top();
	S.pop();
	Point res = S.top();
	S.push(P);
	return res;
}

void convexHull(int N) {
    // First take the bottom most point.
	int ymin = pointList[0].y, index = 0;
	for (int i = 1; i < N; i++) {
		if (pointList[i].y < ymin || (pointList[i].y == ymin &&
                        pointList[i].x < pointList[index].x)) {
			ymin = pointList[i].y;
			index = i;
		}
	}
	swap(pointList[0], pointList[index]);
	sort(&pointList[1], &pointList[N], cmp);
	S.push(pointList[0]);

	for (int i = 1; i < N; i++) {
		while (S.size() > 1){
            if(orientation(nextToTop(),S.top(), pointList[i]) == 2) break;
			S.pop();
		}
		S.push(pointList[i]);
	}
	cnt = 0;
	while (!S.empty()) {
		hullPoints[cnt++] = S.top();
		S.pop();
	}
}

void print_Hull_Points(){
	printf("Total Points: %d\n", cnt);
	for (int i = cnt - 1; i >= 0; i--){
		printf("(%lld,%lld)\n", hullPoints[i].x, hullPoints[i].y);
	}
}

int main() {
	// N is the number of points.
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		Point obj;
		scanf("%lld%lld", &obj.x, &obj.y);
		pointList[i] = obj;
	}
	convexHull(N);
	print_Hull_Points();
	return 0;
}
