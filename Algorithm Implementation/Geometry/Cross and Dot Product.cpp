struct Point {
	int x, y;
};

/// Compute A X B:
int cross(Point A, Point B){
    return (A.x * B.y - A.y * B.x);
}

/// Compute A dot B:
int dot(Point A, Point B){
    return (A.x * B.x + A.y * B.y);
}
