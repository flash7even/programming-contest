/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Each cell of matrix is a pile.
    In each move a player can move stone to down or right cell.
    Who gives last move win.
**/


#define INF 99999999


int main() {
    int nCase,r,c,a;
    sf("%d", &nCase);
    for (int cs = 1; cs <= nCase; cs++) {
        scanf("%d %d", &r, &c);
        int xsum = 0;
        for(int i = 1;i<=r;i++){
            for(int j = 1;j<=c;j++){
                sf("%d",&a);
                if((r+c)%2 != (i+j)%2) xsum ^= a;
            }
        }
        if(xsum != 0) printf("Case %d: win\n", cs);
        else printf("Case %d: lose\n", cs);
    }
    return 0;
}
