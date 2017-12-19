/// Call isInsideConvexPolygon()
/// Returns true/false if the polygon is inside
/// Polygon must be convex
/// Note: Not tested yet, check carefully

int N; /// Total number of points
vector<Point> List;

bool isLeft(Point A, Point B, Point C){
    if(crossABC(A, B, C) >= 0) return true;
    return false;
}

/// The point lie inside the triangle only if,
/// the point is at the same side of each of the side of that triangle.
bool insideTriangle(Point A, Point B, Point C, Point P){
    if(isLeft(P,A,B) == isLeft(P,B,C) && isLeft(P,B,C) == isLeft(P,C,A)) return true;
    return false;
}

/// Find the immediate close point who is at the right side of (List[0] - P) vector.
int bSearchPolygon(Point P){
    int L = 1, R = N-2;
    while (abs(L-R)>5){
        int M = (L+R)/2;
        if (isLeft(List[0], List[M], P)) L = M;
        else R = M;
    }
    for(int M = R;M>=L;M--){
        if (isLeft(List[0], List[M], P)){
            return M;
        }
    }
    return L;
}


bool isInsideConvexPolygon(Point P){
    int pos = bSearchPolygon(P);
    /// List[0] is the lower left most point:
    return insideTriangle(List[0], List[pos], List[pos+1], P);
}
