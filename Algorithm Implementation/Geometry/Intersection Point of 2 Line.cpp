/// Find intersection points of two lines.
/// Use int or double depending on the input format.
/// Driver function: findIntersectionPoint().
/// Complexity: O(1).

#define piii pair<pair<int, int>, int>
#define MP make_pair
#define ff first
#define ss second
#define pb push_back

struct Point {
	int x, y;
};

/// Returns the polygon area of the polygon in List:
double polygonArea(vector<Point> List){
	double area = 0;
	for (int i = 1;i + 1<List.size();i++){
		area += (List[i].y - List[0].y) * (List[i + 1].x - List[i].x)
				- (List[i].x - List[0].x) * (List[i + 1].y - List[i].y);
	}
	return fabs(area / 2.0);
}

/// Returns A,B,C of the equation Ax + By = C.
piii findLineEquation(Point P1, Point P2){
	int A = P2.y - P1.y;
	int B = P1.x - P2.x;
	int C = A * P1.x + B * P1.y;
	return MP(MP(A,B), C);
}

/// P1 and P2 are end points of line 1 and P3 and P4 are end point of line 2.
Point P1, P2, P3, P4;

void findIntersectionPoint(){
	piii L1 = findLineEquation(P1,P2);
	int A1 = L1.ff.ff, B1 = L1.ff.ss, C1 = L1.ss;

	piii L2 = findLineEquation(P3,P4);
	int A2 = L2.ff.ff, B2 = L2.ff.ss, C2 = L2.ss;

	int dif = A1 * B2 - A2 * B1; /// slope difference of the two lines

	if(dif == 0){ /// the lines are either collinear or parallel.
		vector<Point> List;
		List.pb(P1); List.pb(P3); List.pb(P4); List.pb(P2);
		if (polygonArea(List) == 0){
			printf("Collinear\n");
		}else{
			printf("Parallel\n");
		}
	}else{
		double x = (B2 * C1 - B1 * C2) / dif;
		double y = (A1 * C2 - A2 * C1) / dif;
		cout << x << " " << y << endl;
	}
}
