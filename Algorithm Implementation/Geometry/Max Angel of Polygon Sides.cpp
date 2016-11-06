/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

struct Point {
	LL x, y;
};

Point pointList[Size];
Point hullPoints[Size];
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

double angle(Point o, Point a, Point b) {
	Point t1, t2;
	t1.x = a.x - o.x;
	t1.y = a.y - o.y;
	t2.x = b.x - o.x;
	t2.y = b.y - o.y;
	double theta = atan2((double)t2.y, (double)t2.x) -
                   atan2((double)t1.y, (double)t1.x);
    if(theta < -eps) theta += (2.0 * pi);
	return theta;
}

double getMaxAngelInPolygon(){
    if(cnt<3) return 0;
    double res = angle(hullPoints[0], hullPoints[1], hullPoints[cnt-1]);
    hullPoints[cnt] = hullPoints[0];
    for(int i = 1; i < cnt; i++) {
        double ang = angle(hullPoints[i], hullPoints[i+1], hullPoints[i-1]);
        if(ang + eps < res) res = ang;
    }
    return res;
}

int main() {
    int N,nCase;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            Point obj;
            scanf("%lld %lld", &obj.x, &obj.y);
            pointList[i] = obj;
        }
        convexHull(N);
        int i = 0,j = cnt-1;
        while(i<j){
        	swap(hullPoints[i],hullPoints[j]);
        	i++,j--;
        }
        double res = getMaxAngelInPolygon();
        res = eps + res*180.0/pi;
        pf("Case %d: %.7lf\n",cs,res);
    }
	return 0;
}
