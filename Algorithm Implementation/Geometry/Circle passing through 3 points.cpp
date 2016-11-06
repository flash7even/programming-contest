/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 100005
#define INF (1<<30)
#define MOD 1000000007

int main(){
    double angle;
    double x1,x2,x3,y1,y2,y3;
    while(cin>>x1>>y1>>x2>>y2>>x3>>y3){
        double x = (double)sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        double y = (double)sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
        double z = (double)sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
        if(y*y+z*z-x*x == 0 || 2*y*z == 0) angle = 0;
        else angle = (y*y+z*z-x*x)/(2*y*z);
        // x/SinA = 2R;
        double sinA = sqrt(1-angle*angle);
        double crcmfrnc = pi*x/sinA;
        printf("%.2f\n",crcmfrnc);
    }
}
