#include <bits/stdc++.h>
using namespace std;
#define Size 100000005
#define Mod 1000000007

void factFactorize ( LL n ) {
    for (int i = 0;i<pFactor.size();i++) {
        LL x = n;
        LL freq = 0;
        while ( x / pFactor[i] ) {
            freq += (x / pFactor[i]);
            x = x / pFactor[i];
        }
        printf ( "%lld^%lld\n", pFactor[i], freq );
    }
}
