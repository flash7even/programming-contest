/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
    Problem Name : Array GCD
    Algorithm : DP + Greedy + Number Theory
    Link : http://codeforces.com/contest/624/problem/D
**/

#define INF 999999999999999999
///DP[position][subarray to cut not started/started/finished]

LL DP[1000005][3];
int A[1000005];
int N, X, Y;
vector<int> pfactorList;
int totalFactor;

void primeFactorize(int n){
    if (n % 2 == 0){
        pfactorList.pb(2);
        while (n % 2 == 0){
            n /= 2;
        }
    }
    for (int i = 3; i * i <= n; i += 2){
        if (n % i == 0){
            pfactorList.pb(i);
            while (n % i == 0){
                n /= i;
            }
        }
    }
    if (n > 1){
        pfactorList.pb(n);
    }
}

LL solve(int fac){
    for (int i = 1; i <= N; ++i){
        for (int j = 0; j < 3; ++j){
            DP[i][j] = INF;
        }
    }
    //We'll try to select each number at each step.
    //From all options we'll save the optimal one from current state.
    /// 0 - the cut segment has not started yet.
    /// 1 - the cut segment started before but has not finished yet.
    /// 2 - the cut segment started before and already finished.
    for (int i = 1; i <= N; ++i){
        //We are making a cut segment.
        //We can start new one here.
        //Or continue the previous one we started before.
        DP[i][1] = min(DP[i - 1][1] + X, DP[i - 1][0] + X);

        //As we are selecting cur value so we must update
        //for the previous results where
        // 0 - we did not start any cut segment and
        // 2 - we already finished the cut segment.
        if (A[i] % fac == 0){
            DP[i][0] = DP[i - 1][0];
            DP[i][2] = min(DP[i - 1][2], DP[i - 1][1]);
        }else if (A[i] % fac == 1 || A[i] % fac == fac - 1){
            DP[i][0] = DP[i - 1][0] + Y;
            DP[i][2] = min(DP[i - 1][2] + Y, DP[i - 1][1] + Y);
        }
    }
    return min(DP[N][0], min(DP[N][1], DP[N][2]));
}

int main(){
    fast_cin;
    cin >> N >> X >> Y;
    for (int i = 1; i <= N; ++i){
        cin >> A[i];
    }
    for (int t = -1; t <= 1; ++t){
        primeFactorize(A[1] + t);
        primeFactorize(A[N] + t);
    }
    totalFactor = pfactorList.size();
    sort(pfactorList.begin(),pfactorList.end());
    LL res = INF;
    // We'll check for each prime factor if making it the GCD
    // What minimum result we can get building the new sequence.
    for (int i = 0;i<totalFactor;i++){
        if(i>0 && pfactorList[i] == pfactorList[i-1]) continue;
        int f = pfactorList[i];
        res = min(res, solve(f));
    }
    cout << res << endl;
    return 0;
}
