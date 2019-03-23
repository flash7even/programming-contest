/// Subset Masking
/// Generate all possible subsets from a given subset (mask)
void subsetMask(int mask) {
    /// subMask is one of the subset of mask
    for (int subMask = mask; subMask > 0; subMask = (mask & (subMask - 1))) {
        int nMask = mask ^ subMask;
        /// nMask is the new mask excluding the subset subMask
    }
}

/// Find number of elements who has got x as a subset in their bit mask

LL DP[(1<<MXB)+50];
LL TMP[(1<<MXB)+50][MXB+50];
LL CNT[(1<<MXB)+50];
/// DP[x] = Number of elements who contains at least x as a sub mask
/// CNT[x] = Number of times x occur in the input array
/// TMP is just a temporary array used in the processing
/// MXB is maximum number of bit
/// Call getMaskCount() passing input array and it's size

void getMaskCount(int *A, int N){
    CLR(TMP, 0);CLR(DP, 0);CLR(CNT, 0);
    for(int i = 0;i<N;i++){
        CNT[A[i]]++;
        DP[A[i]]++;
    }
    for(int i = (1<<MXB)-1;i>=0;i--){
        int cnt = 0;
        for(int j = 0;j<MXB;j++){
            if(!Check(i, j)){
                if(cnt == 0) DP[i] += DP[i|(1<<j)];
                else DP[i] += TMP[i|(1<<j)][cnt];
                cnt++;
            }
        }
        cnt = 1;
        for(int j = 0;j<MXB;j++){
            if(!Check(i, j)){
                if(cnt == 1){
                    TMP[i][cnt] = DP[i]-DP[i|(1<<j)];
                }else{
                    TMP[i][cnt] = TMP[i][cnt-1]-TMP[i|(1<<j)][cnt-1];
                }
                cnt++;
            }
        }
    }
}
