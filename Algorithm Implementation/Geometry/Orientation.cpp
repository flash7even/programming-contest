/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;


struct Point{
    double x,y;
};

int orientation(Point P, Point Q, Point R) {
	LL ret = (Q.y - P.y) * (R.x - Q.x) - (Q.x - P.x) * (R.y - Q.y);
	if (ret > 0) return 1; /// Polar angle of (P-R) is smaller than (P-Q) with respect to x axis.
	if (ret < 0) return 2; /// Polar angle of (P-R) is greater than (P-Q) with respect to x axis.
	return 0; /// Co linear
}
