/// Sieve
bool mark[Size];/// if mark[u] = 1, it's prime
vector<int> prime;

void sieve(){
    CLR (mark, true);
    mark [0] = mark [1] = false;
    for(int i = 4;i<Size;i+=2) mark [i] = false;
    for(int i = 3;i*i<=Size;i+=2){
        if(mark[i]){
            for(int j=i*i;j<Size;j+=2*i){
                mark [j] = false;
            }
        }
    }
    prime.pb(2);
    for(int i = 3;i<Size;i+=2){
        if(mark[i]) prime.pb(i);
    }
}

/// Segmented Sieve
/// Find the primes between range u to v
/// Works when u, v <= 1e18 but (v-u) <= 1e6

#define rngSize 100505
int segment[rngSize/64];
vector<int> prime; /// Store first 5000 primes excluding 2

#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))

void segmentedSieve(int a, int b){
    if(a <= 2 && 2 <= b){
        printf("2\n"); /// prime
    }
    if (b < 2) return;
    if (a < 3) a = 3;
    if (a % 2 == 0) a++;
    CLR(segment, 0);
    for(int i = 0;i<SZ(prime) && SQ(prime[i]) <= b; i++){
        unsigned j = prime[i] * ((a + prime[i] - 1) / prime[i]);
        if (j % 2 == 0) j += prime[i];
        for (int k = (prime[i] << 1);j <= b;j+=k){
            if (j != prime[i]) {
                setC(segment, (j - a));
            }
        }
    }
    for(int i = 0; i <= b - a;i+=2){
        if (!chkC(segment, i)) {
            printf("%d\n",i+a); /// prime
        }
    }
}

/// Bitwise Sieve
#define Size 100000500
LL mark[Size/64 + 100];

void bitwiseSieve() {
    LL sqrtn = sqrt(Size)+1;
    for (long long i = 3; i <= sqrtn; i += 2) {
        if (!(mark[i / 64] & (1LL << (i % 64)))) {
            for (long long j = i * i; j <= Size; j += 2 * i) {
                mark[j / 64] |= (1LL << (j % 64));
            }
        }
    }
    for (long long i = 3; i <= Size; i += 2) {
        if (!(mark[i / 64] & (1LL << (i % 64)))) {
            /// i is prime.
        }
    }
}
