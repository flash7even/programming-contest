#include <bits/stdc++.h>
using namespace std;

struct matrix{
    LL m[4][4];
};

matrix multiply(matrix a, matrix b){
    matrix t;
    for(int r = 0;r<4;r++){
        for(int c = 0;c<4;c++){
            t.m[r][c] = 0;
            for(int k = 0;k<4;k++){
                t.m[r][c] += (a.m[r][k] * b.m[k][c]);
                t.m[r][c] %= MOD;
            }
        }
    }
    return t;
}

matrix bigMod(matrix mat, LL p){
    if(p == 1) return mat;
    if(p%2 == 1) {
        return multiply(mat,bigMod(mat,p-1));
    } else {
        matrix res = bigMod(mat,p/2);
        return multiply(res,res);
    }
}

LL a, b, n, c;
matrix bMat,rMat,A;

void initMat(){
        bMat.m[0][0] = a;
        bMat.m[0][1] = 0;
        bMat.m[0][2] = b;
        bMat.m[0][3] = 1;

        bMat.m[1][0] = 1;
        bMat.m[1][1] = 0;
        bMat.m[1][2] = 0;
        bMat.m[1][3] = 0;

        bMat.m[2][0] = 0;
        bMat.m[2][1] = 1;
        bMat.m[2][2] = 0;
        bMat.m[2][3] = 0;

        bMat.m[3][0] = 0;
        bMat.m[3][1] = 0;
        bMat.m[3][2] = 0;
        bMat.m[3][3] = 1;

        A.m[0][0] = 0;
        A.m[1][0] = 0;
        A.m[2][0] = 0;
        A.m[3][0] = c;
}

int main(){
    int nCase;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%lld %lld %lld %lld", &n, &a, &b, &c);
        initMat();
        if (n <= 2) {
            printf("Case %d: 0\n",cs);
        } else {
            rMat = bigMod(bMat, n - 2);
            rMat = multiply(rMat,A);
            int nthVal = rMat.m[0][0];
            printf("Case %d: %lld\n",cs,nthVal);
        }
    }
    return 0;
}
