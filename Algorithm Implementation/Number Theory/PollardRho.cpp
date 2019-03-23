/// Generate prime till sqrt(1e9) in vector prime
/// plen = total number of generated primes
/// Include mulmod() and bigmod2() from base template
/// Call factorize to generate all prime factors

struct pollardRhoFactorize{

    /// Using miller rabin but works only for p>1e9
    int isPrime(LL p){
        if (p < 2 || !(p&1)) return 0;
        if (p == 2) return 1;
        LL q = p-1, a, t;
        int k = 0, b = 0;
        while (!(q&1))    q >>= 1, k++;
        for(int it = 0; it < 2; it++){
            a = rand()%(p-4) + 2;
            t = bigmod2(a, q, p);
            b = (t == 1) || (t == p-1);
            for(int i = 1; i < k && !b; i++){
                t = mulmod(t, t, p);
                if (t == p-1) b = 1;
            }
            if(b == 0) return 0;
        }
        return 1;
    }

    LL pollardRho(LL n, LL c){
        LL x = 2, y = 2, i = 1, k = 2, d;
        while(true){
            x = (mulmod(x, x, n) + c);
            if (x >= n)    x -= n;
            d = gcd(x - y, n);
            if (d > 1) return d;
            if (++i == k) y = x, k <<= 1;
        }
        return n;
    }

    void factorizeSmall(int n, vector<LL> &f){
        for (int i = 0; i < plen && prime[i]*prime[i] <= n; i++){
            if (n%prime[i] == 0){
                while (n%prime[i] == 0){
                    f.pb(prime[i]), n /= prime[i];
                }
            }
        }
        if (n != 1)    f.pb(n);
    }

    /// f will contain all the prime factors of n
    void factorize(LL n, vector<LL> &f){
        if(n == 1) return;

        if(n < 1e+9){
            factorizeSmall(n, f);
            return ;
        }
        if(isPrime(n)){
            f.pb(n);
            return;
        }
        LL d = n;
        for(int i = 2; d == n; i++){
            d = pollardRho(n, i);
        }
        factorize(d, f);
        factorize(n/d, f);
    }
} pollard;
