/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Given N piles a player can remove any number of stone from a pile to it's left.
**/

#define INF 99999999

int main() {
    int nCase,n,a,b;
    sf("%d", &nCase);
    for (int cs = 1; cs <= nCase; cs++) {
        scanf("%d", &n);
        int xsum = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a);
            xsum ^= (a);
        }
        if(xsum != 0) printf("Case %d: Alice\n", cs);
        else printf("Case %d: Bob\n", cs);
    }
    return 0;
}
