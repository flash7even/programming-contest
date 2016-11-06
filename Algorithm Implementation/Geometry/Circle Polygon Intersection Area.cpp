/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.0);

struct Point{
    double x, y;
    Point() {
    }
    Point (double tx,double ty){
        x = tx;
        y = ty;
    }
    Point operator - (const Point &t) const{
        Point res;
        res.x = x - t.x;
        res.y = y - t.y;
        return res;
    }
};

Point p[4];

double Dot_Product(Point &a, Point &b, Point &c){
    return (b.x-a.x)*(c.x-a.x) + (b.y-a.y)*(c.y-a.y);
}

double Cross_Product(Point &a, Point &b, Point &c){
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

/// Cross product of two points:
double cp(Point &a, Point &b){
    return a.x*b.y - b.x*a.y;
}

/// The angle between two vectors:
double angle(Point &a, Point &b){
    double ans = fabs((atan2(a.y, a.x) - atan2(b.y, b.x)));
    return ans > pi+eps ? 2*pi-ans : ans;
}

/// Straight line with respect to center and circle intersection:
void Circle_Line_Intersection(Point center, double r, Point l1, Point l2, Point& p1, Point& p2){
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

/// Intersected Area of a circle and a simple polygon:
double Circle_Polygon_Intersection(Point center, double R, Point *p, int n){
    Point o(0,0), a, b, t1, t2;
    double sum = 0, res = 0;
    p[n] = p[0];

    for (int i = 0; i < n; i++) {

        a = p[i]-center;
        b = p[i+1]-center;
        double sign = cp(a,b) > 0 ? 1 : -1;
        double d1 = a.x*a.x + a.y*a.y;
        double d2 = b.x*b.x + b.y*b.y;
        double d3 = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));

        if (d1 < R*R+eps && d2 < R*R+eps) {   /// two points are inside the circle
            res = fabs(cp(a, b));

        } else if (d1 < R*R-eps || d2 < R*R-eps) {   /// only a point inside a circle
            Circle_Line_Intersection(o, R, a, b, t1, t2);
            if ((a.x-t2.x)*(b.x-t2.x) < eps && (a.y-t2.y)*(b.y-t2.y) < eps) {
                t1 = t2;
            }
            if (d1 < d2) {
                res = fabs(cp(a, t1)) + R*R*angle(b, t1);
            } else {
                res = fabs(cp(b, t1)) + R*R*angle(a, t1);
            }

        } else if (fabs(cp(a, b))/d3 > R-eps) {
            /// two points in the garden outside, and only a segment of a circle as much as the intersection
            res = R*R*angle(a, b);

        } else {    /// line and circle there are two intersections
            Circle_Line_Intersection(o, R, a, b, t1, t2);
            if (Dot_Product(t1, a, b) > eps || Dot_Product(t2, a, b) > eps) {
                res = R*R*angle(a, b);
            } else {
                res = fabs(cp(t1, t2));
                if (Cross_Product(t1, t2, a) < eps){
                    res += R*R*(angle(a, t1) + angle(b, t2));
                } else {
                    res += R*R*(angle(a, t2) + angle(b, t1));
                }
            }
        }

        sum += res * sign;
    }

    return fabs(sum)/2.0;
}

int main(){
    int nCase;
    scanf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        Point center;
        double R;
        scanf("%lf %lf %lf",&center.x,&center.y,&R);
        double a,b,c,d;
        scanf("%lf %lf %lf %lf",&a,&b,&c,&d);
        p[0] = Point(a,b);
        p[1] = Point(c,b);
        p[2] = Point(c,d);
        p[3] = Point(a,d);
        printf("Case %d: %lf\n",cs,Circle_Polygon_Intersection(center,R,p,4));
    }
    return 0;
}
