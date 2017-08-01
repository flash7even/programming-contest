int N,H;
int A[2005];
LL DP[2005][2005];
/// DP[i][k] = We are at i'th position and we have k open intervals till now.

LL call(int pos, int opn){
    if(opn < 0) return 0;
    if(pos == N){
        if(opn == 0) return 1;
        return 0;
    }
    if(DP[pos][opn] != -1) return DP[pos][opn];
    LL res = 0;

    if(A[pos] + opn > H) return 0; /// We can't decrease the value.
    if(A[pos] + opn < H-1) return 0; /// We can only increase the value by 1 opening a new interval. But not more that that.

    if(A[pos] + opn == H-1){
        res += call(pos+1, opn+1); /// Open another interval now.
        res += call(pos+1, opn); /// Open another interval and immediately close it.
        res += (call(pos+1, opn)*opn)%mod; /// Open another interval and close one of the open interval.
    }else if(A[pos] + opn == H){
        res += call(pos+1, opn); /// Skip the current element.
        res += (call(pos+1, opn - 1)*opn)%mod; /// Close an interval here.
    }

    return DP[pos][opn] = res%mod;
}

int main() {
    scanf("%d %d",&N,&H);
    for(int i = 0;i<N;i++){
        scanf("%d",&A[i]);
    }
    CLR(DP,-1);
    cout << call(0, 0) << endl;
    return 0;
}
