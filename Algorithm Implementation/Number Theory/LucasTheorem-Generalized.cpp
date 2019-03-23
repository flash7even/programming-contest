/// Lucas Theorem (Generalized)
/// Calculate nCr, When mod is not prime
/// And also mod % (p^q) == 0
/// Where p is a prime and q>1
/// Works very fast when n, r <= 1e18 and mod <= 1e6
/// Call findNCR(n, r, mod) to find answer

LL fact[Size+5];
vector<pii> pDivs;
vector<LL> VL, VN, VR, VM, VE;
vector<LL> N_js, M_js, R_js;
vector<LL> tmp1, tmp2;

struct nCrModNotPrime{
    LL mod;

    void findFactorial(LL p) {
        fact[0] = fact[1] = 1;
        for (LL i = 2; i < mod; i++) {
            if(i%p == 0) fact[i] = fact[i-1];
            else fact[i] =  (fact[i - 1] * i)%mod;
        }
    }

    vector<LL> toBase(LL a,LL b) {
        tmp1.clear();
        while(a) {
            tmp1.pb(a%b);
            a /= b;
        }
        return tmp1;
    }

    vector<LL> compute_js(vector<LL >v, LL p, LL q){
        LL Len = v.size();
        tmp2.clear();
        tmp2.resize(Len);
        for(int i = 0;i<Len;i++){
            LL a = 0,P = 1;
            for(LL j = i; j<Len && j < i+q ; j++){
                a += (v[j]*P);
                P *= p;
            }
            tmp2[i] = a;
        }
        return tmp2;
    }

    vector<LL> computeE(LL Len, vector<LL> VM, vector<LL> VR, LL p){
        LL m = VM.size(), r = VR.size(), c = 0;
        tmp2.clear();
        tmp2.resize(Len);
        for(int i = m;i<Len;i++) VM.pb(0);
        for(int i = r;i<Len;i++) VR.pb(0);
        for(int i = 0;i<Len;i++){
            c += VM[i];
            c += VR[i];
            c /= p;
            tmp2[i] = c;
        }
        for(int i = Len-2;i>=0;i--) tmp2[i] = tmp2[i] + tmp2[i+1];
        return tmp2;
    }

    LL generelizeLucasTheoram(LL n, LL r, LL p, LL q){
        LL m = (n-r);
        VN = toBase(n,p);
        VR = toBase(m,p);
        VM = toBase(r,p);
        N_js = compute_js(VN, p, q);
        M_js = compute_js(VM, p, q);
        R_js = compute_js(VR, p, q);
        LL n_len = VN.size(), m_len = VM.size(), r_len = VR.size();
        VE = computeE(n_len, VR, VM, p);
        LL ans = 1;
        mod = power(p, q);
        findFactorial(p);
        for(int i = 0;i<VE[0];i++) ans = (ans*p)%mod;
        for(int i = 0;i<n_len;i++) ans = (ans*fact[N_js[i]%mod])%mod;
        for(int i = 0;i<m_len;i++) ans = (ans*modInv(fact[M_js[i]%mod], mod))%mod;
        for(int i = 0;i<r_len;i++) ans = (ans*modInv(fact[R_js[i]%mod], mod))%mod;
        if((p != 2 || q<3) && (q<=VE.size() && VE[q-1]%2)) ans = (-1*ans)%mod;
        if(ans<0) ans += mod;
        return ans;
    }

    void primeFactorize(LL n){
        pDivs.clear();
        LL cnt = 0 ;
        while(n % 2 == 0) {
            n>>=1, cnt++;
        }
        if(cnt) pDivs.pb(pii(2, cnt));
        LL sq = sqrt(n) + 1;
        for(LL i = 3;i<=sq;i+=2){
            cnt = 0;
            while(n%i == 0) n /= i, cnt++;
            if(cnt) pDivs.pb(pii(i, cnt));
        }
        if(n>1) pDivs.pb(pii(n, 1));
    }

    LL CRT(LL m) {
        int i = 0;
        LL ans = 0;
        vector<pii>::iterator it;
        for (it = pDivs.begin();it != pDivs.end(); ++it){
            LL p = power((*it).ff, (*it).ss);
            LL e = ((m/p) * modInv(m/p, p))%m;
            ans = (ans + (VL[i] * e)%m)%m;
            i++;
        }
        if(ans<0) ans += m;
        return ans;
    }

    LL findNCR(LL n, LL r, LL m) {
        primeFactorize(m);
        VL.clear();
        vector<pii>::iterator it;
        for (it = pDivs.begin();it != pDivs.end(); ++it){
            VL.pb(generelizeLucasTheoram(n, r, (*it).first, (*it).second));
        }
        return CRT(m);
    }
}ncr;
