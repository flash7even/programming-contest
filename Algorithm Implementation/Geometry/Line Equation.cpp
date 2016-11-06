/// Two points P(x1,y1) and Q(x2,y2) form a line which equation is y1 = m*x1+c or y2 = m*x2+c .
/// If two line equations have same value of m and c , than all 4 co-ordinates are co-linear .

/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

struct Point{
    double x , y ;
};

int main(){
    Point P = {0,0} , Q = {5,7};
    double m = (Q.y - P.y)/(Q.x - P.x);
    double c = P.y - P.x*m;
    cout << "SLOPE: " << m << " " << " CONS: " << c << endl ;
    return 0;
}
