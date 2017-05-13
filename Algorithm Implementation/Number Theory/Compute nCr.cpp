#define forab(i,a,b) for (__typeof(b) i = (a); i <= (b); ++i)
#define rep(i,n) forab (i, 0, (n) - 1)
#define For(i,n) forab (i, 1, n)
#define rofba(i,a,b) for (__typeof(b) i = (b); i >= (a); --i)
#define per(i,n) rofba (i, 0, (n) - 1)
#define rof(i,n) rofba (i, 1, n)
#define forstl(i,s) for (__typeof ((s).end ()) i = (s).begin (); i != (s).end (); ++i)

LL mod;
LL fact[Size+5];
vector<pii> primeDivisors;
vector<LL> L, N, R, M, e;
vector<LL> N_js, M_js, R_js;

void findFactorial(LL p) {
    fact[0] = fact[1 ]= 1;
    LL i;
    for (i = 2; i < mod; i++) {
        if(i%p==0) fact[i] = fact[i-1];
        else fact[i] =  (fact[i - 1] * i)%mod;
    }
}

vector<LL > v;

vector<LL > tobase(LL a,LL b) {
    v.clear();
    while(a) {
        v.pb(a%b);
        a /= b;
    }
    return v;
}

vector<LL > tmp;

vector<LL > compute_js(vector<LL >v,LL p,LL q) {
    LL len = v.size();
    tmp.clear();
    tmp.resize(len);
    rep(i,len) {
        LL a = 0,P = 1;
        for(LL j = i; j<len && j < i+q ; j++) {
            a += (v[j]*P);
            P *= p;
        }
        tmp[i] = a;
    }
    return tmp;
}

vector<LL > computeE(LL len,vector<LL >M,vector<LL >R,LL p) {
    LL m = M.size(),r = R.size(),c = 0;
    tmp.clear();
    tmp.resize(len);
    forab(i,m,len-1) M.pb(0);
    forab(i,r,len-1) R.pb(0);
    rep(i,len) {
        c += M[i];
        c += R[i];
        c /= p;
        tmp[i] = c;
    }
    per(i,len-1) tmp[i] = tmp[i] + tmp[i+1];
    return tmp;
}

LL generelizeLucasTheoram(LL n,LL r,LL p,LL q) {
    LL m = (n-r);
    N = tobase(n,p);
    R = tobase(m,p);
    M = tobase(r,p);
    N_js = compute_js(N,p,q);
    M_js = compute_js(M,p,q);
    R_js = compute_js(R,p,q);
    LL n_len = N.size() , m_len = M.size() , r_len = R.size();
    e =computeE(n_len,R,M,p);
    LL ans = 1;
    mod = power(p,q);
    findFactorial(p);
    rep(i,e[0]) ans = (ans*p)%mod;
    rep(i,n_len) ans = (ans*fact[N_js[i]%mod])%mod;
    rep(i,m_len) ans = (ans*modInv(fact[M_js[i]%mod],mod))%mod;
    rep(i,r_len) ans = (ans*modInv(fact[R_js[i]%mod],mod))%mod;
    if((p != 2 || q<3) && (q<=e.size() && e[q-1]%2)) ans = (-1*ans)%mod;
    return ans<0?ans+mod:ans;
}

void primeFactorize(LL n) {
    primeDivisors.clear();
    LL cnt = 0 ;
    while(n % 2 == 0 ) {
        n>>=1 , cnt++;
    }
    if(cnt) primeDivisors.pb( pii(2,cnt) );
    LL sq = sqrt(n) + 1 ;
    for( LL i = 3 ; i <= sq ; i += 2 ) {
        cnt = 0 ;
        while(n % i == 0 ) n /= i , cnt++ ;
        if(cnt) primeDivisors.pb( pii(i,cnt) );
    }
    if(n > 1 ) primeDivisors.pb( pii(n,1) ) ;
}


LL CRT(LL m) {
    int i = 0;
    LL ans = 0;
    forstl(it,primeDivisors) {
        LL p = power((*it).first,(*it).second);
        LL e = ((m/p) * modInv(m/p,p))%m;
        ans = (ans + (L[i] * e)%m)%m;
        i++;
    }
    return ans<0?ans+m:ans;
}

/// Calculate nCr when mod value is not prime.
LL nCrWhenMnotPrime(LL n, LL r, LL m) {
    primeFactorize(m);
    L.clear();
    forstl(it,primeDivisors) {
        L.pb(generelizeLucasTheoram(n,r,(*it).first,(*it).second));
    }
    return CRT(m);
}
