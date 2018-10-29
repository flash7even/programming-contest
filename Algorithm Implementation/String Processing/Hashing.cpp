/**
    1. Store the corresponding integer value of the string digits to S
    2. Set M1 and M2 to 1e9+7 and 1e9+9
    3. Set B1 and B2 to immediate next prime numbers > length(S)
    4. Call preCalc() to calculate bigmod and modInv calculation
    5. Call hashCalc() to calculate the hash value of the whole string
    6. rangeHash() will give the hash value of a substring
**/

const int Size = 100005;

struct doubleHash{

    LL hashsum1[Size], hashsum2[Size];
    LL basePow1[Size], basePow2[Size];
    LL modInv1[Size], modInv2[Size];
    LL S[Size];
    LL B1, B2, M1, M2;

    pll rangeHash(int u, int v){
        LL h1 = hashsum1[v] - hashsum1[u-1];
        LL h2 = hashsum2[v] - hashsum2[u-1];

        if(h1<0) h1 += M1;
        LL mty1 = modInv1[u-1];
        h1 = (h1*mty1)%M1;

        if(h2<0) h2 += M2;
        LL mty2 = modInv2[u-1];
        h2 = (h2*mty2)%M2;

        return MP(h1, h2);
    }

    void preCalc(int N){
        basePow1[0] = 1;
        basePow2[0] = 1;
        modInv1[0] = modInv(1, M1);
        modInv2[0] = modInv(1, M2);
        FOR(i,1,N){
            basePow1[i] = (basePow1[i-1]*B1)%M1;
            basePow2[i] = (basePow2[i-1]*B2)%M2;
            modInv1[i] = modInv(basePow1[i], M1);
            modInv2[i] = modInv(basePow2[i], M2);
        }
    }

    void hashCalc(int N){
        FOR(i,1,N){
            LL add = (S[i]*basePow1[i-1])%M1;
            hashsum1[i] = (hashsum1[i-1] + add)%M1;
            add = (S[i]*basePow2[i-1])%M2;
            hashsum2[i] = (hashsum2[i-1] + add)%M2;
        }
    }

}hashing;
