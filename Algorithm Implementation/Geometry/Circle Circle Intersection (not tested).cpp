/**
    Given the center and radius of 2 circle,
    Find the intersection points between them.
 **/

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define sq(a) (a*a)
#define pi 3.1416
#define eps 1e-6
#define LL long long

struct Point{
	double x,y;
};

struct Circle{
	double r;
	Point c;
};

Circle a,b;
Point pntInt1,pntInt2;

double Dist(const Point &a, const Point &b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int findIntersectionPoints(const Circle &a, const Circle &b) {
	double d = Dist(a.c,b.c);

	if(d > a.r + b.r) return -1; /// They don't intersect.
	if(d < abs(a.r - b.r)) return -2; /// One contain other.
	if(abs(d - 0)<eps && a.r == b.r) return 0; /// Both are same circle.

	double aa = (sq(a.r) - sq(b.r) + sq(d))/(2.0 * d);
	double bb = d - aa;
	double h = sqrt(sq(a.r) - sq(aa));

	Point P0 = a.c,P1 = b.c,P2;

	double dx = P1.x - P0.x;
	double dy = P1.y - P0.y;
	double rx = -dy * (h/d);
	double ry = dx * (h/d);

	P2.x = P0.x + (aa * dx)/d;
	P2.y = P0.y + (aa * dy)/d;


	pntInt1.x = P2.x + rx;
	pntInt1.y = P2.y + ry;
	pntInt2.x = P2.x - rx;
	pntInt2.y = P2.y - ry;

	return 1; /// Found intersection points & saved in pntInt1 & pntInt2.
}

int main() {
	cin >> a.c.x >> a.c.y >> a.r;
	cin >> b.c.x >> b.c.y >> b.r;
	findIntersectionPoints(a,b);
	return 0;
}
