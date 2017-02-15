struct Point {
	int x, y;
};

double polygonArea(vector<Point> List) {
	double area = 0;
	for (int i = 1; i + 1 < List.size(); i++){
		area += (List[i].y - List[0].y) * (List[i + 1].x - List[i].x)
				- (List[i].x - List[0].x) * (List[i + 1].y - List[i].y);
	}
	return fabs(area / 2.0);
}
