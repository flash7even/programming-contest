/// Given N points find the distance of the closest two points.
/// Complexity : O(n (Logn))
/// Driver function: solve().

struct Point {
	double x, y;
};

int cmpX(Point a, Point b) {
	return (a.x < b.x);
}

int cmpY(Point a, Point b) {
	return (a.y < b.y);
}

double distPoints(Point p1, Point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double curMin(double x, double y) {
	return (x < y) ? x : y;
}

double bruteForce(Point P[], int N) {
	double Min = FLT_MAX;
	for (int i = 0; i < N; ++i){
		for (int j = i + 1; j < N; ++j){
			if (distPoints(P[i], P[j]) < Min){
				Min = distPoints(P[i], P[j]);
			}
		}
	}
	return Min;
}

double closestPairInStrip(Point strip[], int Sz, double d) {
	double curMin = d;
	for (int i = 0; i < Sz; ++i){
		for (int j = i + 1; j < Sz && (strip[j].y - strip[i].y) < curMin; ++j){
			if (distPoints(strip[i], strip[j]) < curMin){
				curMin = distPoints(strip[i], strip[j]);
			}
		}
	}
	return curMin;
}

double call(Point Px[], Point Py[], int N) {
	if (N <= 3){
		return bruteForce(Px, N);
	}
	int mid = N / 2;
	Point midPoint = Px[mid];
	Point leftSide[mid + 1];
	Point rightSide[N - mid - 1];
	int leftIdx = 0, rightIdx = 0;
	for (int i = 0; i < N; i++) {
		if (Py[i].x <= midPoint.x) {
			leftSide[leftIdx++] = Py[i];
		} else {
			rightSide[rightIdx++] = Py[i];
		}
	}
	double distLeft = call(Px, leftSide, mid);
	double distRight = call(Px + mid, rightSide, N - mid);
	double minDist = curMin(distLeft, distRight);

	Point strip[N];
	int j = 0;
	for (int i = 0; i < N; i++){
		if (abs(Py[i].x - midPoint.x) < minDist){
			strip[j] = Py[i];
			j++;
		}
	}
	return curMin(minDist, closestPairInStrip(strip, j, minDist));
}

double solve(Point P[], int N) {
	Point Px[N];
	Point Py[N];
	for (int i = 0; i < N; i++) {
		Px[i] = P[i];
		Py[i] = P[i];
	}
	sort(Px,Px+N,cmpX);
	sort(Py,Py+N,cmpY);
	return call(Px, Py, N);
}
