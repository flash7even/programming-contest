/// Given a set of N number points find the smallest convex polygon that contains all the points.
/// Driver function: convexHull().
/// Time Complexity: O(NlogN).

struct Point {
	LL x, y;
};

Point List[Size];
Point Hull[Size];
stack<Point> st;
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
	LL ret = orientation(List[0], X, Y);
	if (ret == 0) {
		LL dist1 = dist(List[0], X);
		LL dist2 = dist(List[0], Y);
		return (dist1 < dist2);
	} else if (ret == 2){
		return true;
	} else {
		return false;
	}
}

Point nextToTop() {
	Point P = st.top();
	st.pop();
	Point res = st.top();
	st.push(P);
	return res;
}

void convexHull(int N){
	int ymin = List[0].y, idx = 0;
	for (int i = 1; i < N; i++) {
		if (List[i].y < ymin || (List[i].y == ymin &&
                        List[i].x < List[idx].x)) {
			ymin = List[i].y;
			idx = i;
		}
	}
	swap(List[0], List[idx]);
	sort(&List[1], &List[N], cmp);
	st.push(List[0]);

	for (int i = 1; i < N; i++) {
		while (st.size() > 1){
            if(orientation(nextToTop(),st.top(), List[i]) == 2) break;
			st.pop();
		}
		st.push(List[i]);
	}
	cnt = 0;
	while (!st.empty()) {
		Hull[cnt++] = st.top();
		st.pop();
	}
}
