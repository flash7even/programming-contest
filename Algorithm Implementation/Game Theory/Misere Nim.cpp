/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    In misere nim who gives last move win.
    When all the pile have 1 stone then xor sum doesn't work.
    Handle that case manually.
**/

#define INF 99999999

int main() {
    int nCase,n,a;
    sf("%d", &nCase);
    for (int cs = 1; cs <= nCase; cs++) {
        scanf("%d", &n);
        int xsum = 0,cntOne = 0;
        for(int i = 0; i < n; i++) {
            scanf("%lld", &a);
            if(a == 1) cntOne++;
            xsum ^= a;
        }
        if(cntOne == n){
            if(n%2 == 0) printf("Case %d: Alice\n", cs);
            else printf("Case %d: Bob\n", cs);
        }else{
            if(xsum != 0) printf("Case %d: Alice\n", cs);
            else printf("Case %d: Bob\n", cs);
        }
    }
    return 0;
}
