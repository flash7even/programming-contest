#include <bits/stdc++.h>
using namespace std;

struct Point{
    double x, y;
};

int N;
vector<Point> List;

/// Compute A X B:
int cross(Point A, Point B){
    return (A.x * B.y - A.y * B.x);
}

/// Compute the cross product AB X AC
int crossProduct(Point A, Point B, Point C) {
    Point AB = {B.x - A.x, B.y - A.y}; /// AB vector
    Point AC = {C.x - A.x, C.y - A.y}; /// AC vector
    return cross(AB, AC);
}

bool isLeft(Point A, Point B, Point C){
    if(crossProduct(A, B, C) >= 0) return true;
    return false;
}

/// The point lie inside the triangle only if,
/// the point is at the same side of each of the side of that triangle.
bool insideTriangle(Point A, Point B, Point C, Point P){
    if(isLeft(P,A,B) == isLeft(P,B,C) && isLeft(P,B,C) == isLeft(P,C,A)) return true;
    return false;
}

/// Find the immediate close point who is at the right side of (List[0] - P) vector.
int bSearch(Point P){
    int L = 1, R = N-1;
    while (L < R){
        int M = (L+R)/2;
        if (isLeft(List[0], List[M], P)) L = M;
        else R = M - 1;
    }
    return L;
}

bool isInside(Point P){
    int pos = bSearch(P);
    /// List[0] is the lower left most point:
    return insideTriangle(List[0], List[pos], List[pos+1], P);
}

int main(){
    return 0;
}
