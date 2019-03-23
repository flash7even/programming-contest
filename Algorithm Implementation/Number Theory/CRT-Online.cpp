/// A is the list of reminders
/// M is the list of mod values
/// Doesn't work when the mod values aren't pairwise co-prime
vector<LL> A, M;

LL CRT(vector<LL> &A, vector<LL> &M){
    myint a1 = A[0], m1 = M[0];
    FOR(i,1,SZ(A)-1){
        LL a2 = A[i], m2 = M[i];
        LL p, q;
        ext_gcd(m1, m2, &p, &q);
        LL mod = m1*m2;
        LL x = ((((a1*m2)%mod)*q)%mod + (((a2*m1)%mod)*p)%mod)%mod;
        a1 = x;
        m1 = mod;
        if(a1<0) a1 += mod;
    }
    if(a1<0) a1 += m1;
    return a1;
}
