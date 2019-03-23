/// Lucas Theorem
/// Lucas theorem calculates nCr%m when m is prime
/// Works fast when m <= 1e3
/// If m is not prime but multiple of some distinct primes
/// Then, calculate nCr for each prime as mod
/// Finally merge them using CRT
/// init() -> addPrime() -> precalc() -> lucasTheorem()

#define MAXPRIME XXX                    // how many primes
#define MAXCOUNT YYY                    // how big is the largest prime

vlong numPrime;                         // number of primes that might be passed as S
vlong primes[MAXCOUNT];                 // value of the i-th prime we will use in primes[i]
vlong location[MAXPRIME];               // location[x] holds position of prime x in primes
vlong modVal[MAXCOUNT][MAXPRIME];
vlong invVal[MAXCOUNT][MAXPRIME];

void init() {
    numPrime = 0;
}

void addPrime(vlong prime) {
    primes[numPrime] = prime;
    location[prime] = numPrime;
    numPrime++;
}

void precalc() {
    for (vlong i=0; i<numPrime; i++) {
        modVal[i][0] = invVal[i][0] = 1;
        for (vlong j=1; j<primes[i]; j++) {
            modVal[i][j] = (modVal[i][j-1] * j) % primes[i];
            invVal[i][j] = modInv(modVal[i][j], primes[i]);
        }
    }
}

vlong nCrModM(vlong n, vlong r, vlong m){
    /// Calculate nCr % m using DP/preprocessing
    /// Note: Here n, r < m (m based number)
    if (n < r) return 0;
    vlong ploc = location[m];
    vlong res = modVal[ploc][n];
    res = (res * invVal[ploc][r]) % m;
    res = (res * invVal[ploc][n-r]) % m;
    return res;
}

vlong lucasTheorem(vlong n, vlong r, vlong m){
   if (n < r) return 0;
   if (r == 0) return 1;
   vlong ni = n%m, ri = r%m;
   vlong res = nCrModM(ni, ri, m);
   if (res == 0) return 0;
   return (res * lucasTheorem(n/m, r/m, m))%m;
}
