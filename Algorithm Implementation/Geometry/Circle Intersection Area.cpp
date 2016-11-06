/**
    Given the center and radius of 2 circle.
    Find the intersection area of them.
 **/

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define sq(a) (a*a)
#define pi 3.1416
#define LL long long

struct Point{
	LL x,y;
};

struct Circle{
	LL r;
	Point c;
};

LL X1,X2,X3,Y1,Y2,Y3;

inline LL sqdist(const Point &a, const Point &b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

inline double commonArea(const Circle &a, const Circle &b) {
    int dsq = sqdist(a.c, b.c);
    double d = sqrt((double)dsq);
    if(sq(a.r + b.r) <= dsq) return 0;
    if(a.r >= b.r && sq(a.r-b.r) >= dsq) return pi * b.r * b.r;
    if(a.r <= b.r && sq(b.r-a.r) >= dsq) return pi * a.r * a.r;
    double angA = 2.0 * acos((a.r * a.r + dsq - b.r * b.r) / (2.0 * a.r * d));
    double angB = 2.0 * acos((b.r * b.r + dsq - a.r * a.r) / (2.0 * b.r * d));
    double a1 = a.r * a.r * (angA - sin(angA));
    double a2 = b.r * b.r * (angB - sin(angB));
    return 0.5 * (a1 + a2);
}
