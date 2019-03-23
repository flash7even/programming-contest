/// Chinese Reminder Theorem
/// Returns the smallest number x such that,
/// x % num[i] = rem[i] for each i
/// Numbers in num[] are pairwise co prime

LL num[Size];
LL rem[Size];

LL CRT(int N){ /// N is size of num/rem
    LL prod = 1;
    for (int i = 0;i<N;i++){
        prod *= num[i];
    }
    LL result = 0;
    for (int i = 0;i<N;i++){
        LL pp = prod / num[i];
        result += rem[i] * modInv(pp, num[i]) * pp;
    }
    return (result % prod);
}
