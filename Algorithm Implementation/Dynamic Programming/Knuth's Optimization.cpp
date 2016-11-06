/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    The problem can be easily solved by old fashioned DP approach.
    But the complexity will become N^2*M which'll get TLE.
    Notice here, we don't need to run the middle loop for each interval.
    There is a quadrangle inequality here which satisfy knuth's conditions.
    So we can apply Knuth's optimization.
    Link : https://www.quora.com/What-is-Knuths-optimization-in-dynamic-programming
**/

#define Size 1005

int N,M;
int A[Size];
int mid[Size][Size];
int DP[Size][Size];
int cost[Size][Size];
int csum[Size];

/// Knuth's Conditions:
/// mid[i,j-1] <= mid[i,j] <= mid[i+1,j]
/// Here, mid[i][j] = k represents the index which gives the optimal answer if we make a partition at k.
/// cost[i][j] represents the cost for the interval i to j.
/// For any a,b,c,d where a <= b <= c <= d :
/// cost[a][c] + cost[b][d] <= cost[a][d] + cost[b][c] (quadrangle inequality).
/// cost[b][c] <= cost[a][d] (monotonicity).

void costFunc(){
    FOR(i,1,N){
        csum[i] = A[i];
        cost[i][i] = 0;
        FOR(j,i+1,N){
            csum[j] = csum[j-1] + A[j];
            cost[i][j] = cost[i][j-1] + csum[j-1]*A[j];
        }
    }
}

/// Check if knuth conditions are valid:
void knuthValidation(){
    int a,b,c,d;
    FOR(i,1,10){
        scanf("%d %d %d %d",&a,&b,&c,&d);
        int acbd = cost[a][c] + cost[b][d];
        int adbc = cost[a][d] + cost[b][c];
        int bc = cost[b][c];
        int ad = cost[a][d];
        printf("   Rule 1: %d <= %d ???\n",acbd,adbc);
        printf("   Rule 2: %d <= %d ???\n",bc,ad);
    }
}

int solve(){
    costFunc();
    knuthValidation();
    FOR(k,1,M){
        mid[N+1][k] = N;
    }

    FOR(i,1,N){
        DP[i][1] = cost[1][i];
        mid[i][1] = 0;
    }

    for (int k = 2; k <= M; k++){
        for (int i = N; i >= 1; i--) {
            int L1 = mid[i][k-1];
            int L2 = mid[i+1][k];
            DP[i][k] = inf;
            /// The optimal answer lie for an index between (L1 - L2).
            /// So we don't need to check for all (1 - i) to make a partition.
            for(int m = L1;m<=L2 && m<i;m++){
                int rs = DP[m][k-1] + cost[m+1][i];
                if(rs < DP[i][k]){
                    DP[i][k] = rs;
                    mid[i][k] = m;
                }
            }
        }
    }
    return DP[N][M];
}

int main () {
    #ifdef forthright48
    freopen ( "input.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    while(sf("%d %d",&N,&M) == 2){
        if(N == 0 && M == 0) break;
        M++;
        FOR(i,1,N){
            inpI(A[i]);
        }
        int res = solve();
        pf("%d\n",res);
    }
    return 0;
}
