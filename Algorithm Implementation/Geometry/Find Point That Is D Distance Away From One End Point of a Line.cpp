struct Point{
    double x,y;
};

/// Find a point C on line AB such that distance
/// from A to C is d.
Point findCRP(Point A, Point B, double d){
    Point vecAB,C;
    vecAB.x = B.x - A.x;
    vecAB.y = B.y - A.y;
    double norm = sqrt(SQ(vecAB.x) + SQ(vecAB.y));
    vecAB.x /= norm;
    vecAB.y /= norm;
    C.x = A.x + d*vecAB.x; /// Note: To find a point D distance outside the line then minus here.
    C.y = A.y + d*vecAB.y;
    return C;
}
