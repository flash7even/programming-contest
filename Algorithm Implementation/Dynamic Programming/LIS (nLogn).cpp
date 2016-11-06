/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

#define Size 100005
#define Mod 1000000007LL

int N;
int A[100005];
int LIS[100005];
int LDS[100005];
vector<int> List;

void calculate_LIS(){
    List.clear();
    for(int i = 0;i<N;i++){
        vector<int>::iterator low = lower_bound(List.begin(),List.end(),A[i]);
        LIS[i] = (low - List.begin());
        if(low == List.end()) List.pb(A[i]);
        else *low = A[i];
    }
}

void calculate_LDS(){
    List.clear();
    reverse(A,A+N);
    for(int i = 0;i<N;i++){
        vector<int>::iterator low = lower_bound(List.begin(),List.end(),A[i]);
        LDS[i] = (low - List.begin());
        if(low == List.end()) List.pb(A[i]);
        else *low = A[i];
    }
    reverse(A,A+N);
    reverse(LDS,LDS+N);
}

void solve(){
    calculate_LIS();
    calculate_LDS();
    /// LIS[i] = length of LIS found till position i;
    /// LDS[i] = length of LDS found till position i;
    int resLIS = 0,resLDS = 0;
    for(int i = 0;i<N;i++){
        resLIS = max(resLIS,LIS[i]);
        resLDS = max(resLDS,LDS[i]);
    }
    pf("LIS: %d , LDS: %d\n",resLIS,resLDS);
}

int main(){
    int nCase;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d",&N);
        for(int i = 0;i<N;i++){
            sf("%d",&A[i]);
        }
        solve();
    }
}
