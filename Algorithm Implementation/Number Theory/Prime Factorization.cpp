vector<pii> primeFactorize(LL num){
    vector<pii> pfactors;
    FOR(i,0,SZ(prime)-1){
    LL pf = prime[i];
    if(pf*pf>num) break;
    if(num%pf == 0){
        int cnt = 0;
        while(num%pf == 0){
        num/=pf;
        cnt++;
        }
        pfactors.pb(MP(pf, cnt));
    }
    }
    if(num>1){
        pfactors.pb(MP(num, 1));
    }
    return pfactors;
}
