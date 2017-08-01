int N,K;
int A[205];
int DP[205][205][1005];
/// DP[i][j][k] = At i'th position, we have j open intervals with total k imbalance value.

LL call(int cur,int opn,int sum){
    if(sum>K || opn<0) return 0;
    if(cur > N){
        if(opn == 0) return 1;
        return 0;
    }
    if(DP[cur][opn][sum] != -1) return DP[cur][opn][sum];
    LL res = 0;
    int nSum = sum + (A[cur] - A[cur-1])*opn;
    /// All the open intervals will have to be closed later
    /// with a greater element. So (A[cur] - A[cur-1]) will contribute to
    /// all of their imbalance. That's why we multiply it by opn.

    res += call(cur+1,opn,nSum);         /// Open a new interval and immediately close it
    res += call(cur+1,opn+1,nSum);       /// Place cur as the first element in a new interval
    res += call(cur+1,opn,nSum)*opn;     /// Place cur in one of the open interval and remain open
    res += call(cur+1,opn-1,nSum)*opn;   /// Place cur in one of the open interval and close it

    return DP[cur][opn][sum] = res%MOD;
}

int main () {
    scanf("%d %d",&N,&K);
    for(int  i = 1;i<=N;i++){
        scanf("%d",&A[i]);
    }
    sort(A+1,A+N+1);
    CLR(DP,-1);
    int res = call(1,0,0);
    cout << res << endl;
    return 0;
}
