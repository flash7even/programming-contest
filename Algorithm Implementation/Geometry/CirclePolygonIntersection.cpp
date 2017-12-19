/// Circle Polygon Intersection Area

double dotBAC(Point A, Point B, Point C){
    return (B.x - A.x)*(C.x - A.x) + (B.y - A.y)*(C.y - A.y);
}

/// Straight line with respect to center and circle intersection:
void circleLineIntersectionArea(Point center, double r, Point l1, Point l2, Point& p1, Point& p2){
    double a1 = l2.x - l1.x;
    double a2 = l2.y - l1.y;
    double b1 = l1.x - center.x;
    double b2 = l1.y - center.y;

    /// Ax + By + C = 0:
    double A = a1*a1 + a2*a2;
    double B = (a1*b1 + a2*b2)*2;
    double C = b1*b1 + b2*b2 - r*r;

    /// t1,t2 are the value of x:
    double t1 = (-B - sqrt(B*B - 4.0*A*C))/2.0/A;
    double t2 = (-B + sqrt(B*B - 4.0*A*C))/2.0/A;

    p1.x = l1.x + a1*t1;
    p1.y = l1.y + a2*t1;
    p2.x = l1.x + a1*t2;
    p2.y = l1.y + a2*t2;
}

/// Parameters (Circle center, circle radius, polygon array, number of points)
double circlePolygonIntersectionArea(Point center, double R, Point *List, int N){
    Point o(0,0), a, b, t1, t2;
    double sum = 0, res = 0;
    List[N] = List[0];

    for (int i = 0; i < N; i++) {
        a = List[i] - center;
        b = List[i+1] - center;
        double sign = crossAB(a,b) > 0 ? 1 : -1;
        double d1 = SQ(a.x) + SQ(a.y);
        double d2 = SQ(b.x) + SQ(b.y);
        double d3 = sqrt(SQ(a.x-b.x) + SQ(a.y-b.y));

        if(d1 < R*R+eps && d2 < R*R+eps){   /// Two points are inside the circle
            res = fabs(crossAB(a, b));
        }else if (d1 < R*R-eps || d2 < R*R-eps){   /// Only a point inside a circle
            circleLineIntersectionArea(o, R, a, b, t1, t2);
            if((a.x-t2.x)*(b.x-t2.x) < eps && (a.y-t2.y)*(b.y-t2.y) < eps){
                t1 = t2;
            }
            if(d1 < d2){
                res = fabs(crossAB(a, t1)) + R*R*angle(b, t1);
            }else{
                res = fabs(crossAB(b, t1)) + R*R*angle(a, t1);
            }

        }else if(fabs(crossAB(a, b))/d3 > R-eps){
            /// Two points in the garden outside, and only a segment of a circle as much as the intersection
            res = R*R*angle(a, b);
        }else{    /// Line and circle there are two intersections
            circleLineIntersectionArea(o, R, a, b, t1, t2);
            if(dotBAC(t1, a, b) > eps || dotBAC(t2, a, b) > eps){
                res = R*R*angle(a, b);
            }else{
                res = fabs(crossAB(t1, t2));
                if (crossABC(t1, t2, a) < eps){
                    res += R*R*(angle(a, t1) + angle(b, t2));
                } else {
                    res += R*R*(angle(a, t2) + angle(b, t1));
                }
            }
        }
        sum += res*sign;
    }
    return fabs(sum)/2.0;
}
