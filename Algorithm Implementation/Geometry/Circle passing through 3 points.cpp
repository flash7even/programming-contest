/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 100005
#define INF (1<<30)
#define MOD 1000000007

struct Point{
    double x,y;
};

void findCircle(Point P1, Point P2, Point P3){
    double angle;
    double x = (double)sqrt(SQ(P2.x-P1.x) + SQ(P2.y-P1.y));
    double y = (double)sqrt(SQ(P3.x-P1.x) + SQ(P3.y-P1.y));
    double z = (double)sqrt(SQ(P2.x-P3.x) + SQ(P2.y-P3.y));
    if(y*y + z*z - x*x == 0 || 2*y*z == 0){
        angle = 0;
    }else{
        angle = (y*y + z*z - x*x)/(2*y*z);
    }
    /// x/SinA = 2R;
    double sinA = sqrt(1-angle*angle);
    double R = x/(sinA*2.0);
    double crcmfrnc = pi*x/sinA;
    printf("%.2f\n",crcmfrnc);
}
