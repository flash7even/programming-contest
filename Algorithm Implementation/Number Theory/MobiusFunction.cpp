/// Mobius function is a function which has one of the following values:
/// mobius(x) = -1 : square free number with odd prime factors
/// mobius(x) = 1  : square free number with even prime factors
/// mobius(x) = 0  : not a square free number
/// Store all the prime till N in vector prime, then call mobiusCalc(N)

int mobius[Size+10];

void mobiusCalc(int n){
    FOR(i,1,n) mobius[i] = 1; ///Initially all value is 1
    ///Mark all numbers with square factors 0
    int sqrtn = sqrt(n)+1;
    FOR(i,0,SZ(prime)-1) {
        if(prime[i]>sqrtn) break;
        int x = SQ(prime[i]);
        for(int j = x; j <= n; j += x) mobius[j] = 0;
    }
    ///For each prime, all it's multiple gets multiplied by -1
    FOR(i,0,SZ(prime)-1){
        for(int j = prime[i]; j <= n; j += prime[i]) mobius[j] *= -1;
    }
}

/// Application of Mobius function:
/// It is mainly used with inclusion exclusion, when items are the first K primes.
/// Complexity is improved from 2^k to NloglogN
/// Ex1: Number of pair (x,y) whose gcd is 1
/// Ex2: Summation of gcd(x,y) for all pair of 1<=x,y<=N
