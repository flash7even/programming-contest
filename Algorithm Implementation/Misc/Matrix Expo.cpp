/**
    Recurrence: f(n+1) = f(n) + f(n-1)
    Given: f(0) = a, f(1) = b
    Matrix Equation: A * X = B
    A = |1 1| X = |f(0)| B = |f(0) + f(1)|
        |1 0|     |f(1)|     |     f1    |
    Find f(n+1) = B = A^n * X

    How To Use?
    1. Call buildMatrix() and store values accordingly
    2. Find B = bigMatMod(A, n - 1)
    3. Find B = multiply(B, X)
    4. Now, f(n) = B.m[0][0]
**/

#define MXR 5 /// Change here
#define MXC 5

struct matrix{
    int R, C;
    LL m[MXR][MXC];
    matrix(){}
    matrix(int r, int c){
        R = r;
        C = c;
    }
    void clear(int r, int c){
        R = r;
        C = c;
    }
};

matrix multiply(matrix a, matrix b){
    matrix res(a.R, b.C);
    for(int r1 = 0; r1<a.R; r1++){
        for(int c1 = 0; c1<a.C; c1++){
            res.m[r1][c1] = 0;
            for(int k = 0; k<a.C; k++){
                res.m[r1][c1] += (a.m[r1][k]*b.m[k][c1]); /// mod here if needed
            }
        }
    }
    return res;
}

matrix bigMatMod(matrix a, LL p){
    if(p == 1) return a;
    if(p%2 == 1) {
        return multiply(a, bigMatMod(a, p-1));
    } else {
        matrix res = bigMatMod(a, p/2);
        return multiply(res, res);
    }
}

matrix A, B, X;
LL a, b; /// f(0) = a, f(1) = b

void buildMatrix(){
    /// Set row column accordingly
    A.clear(2, 2);
    B.clear(2, 1);

    /// Store initial values in the matrix
    A.m[0][0] = 1;
    A.m[0][1] = 1;
    A.m[1][0] = 1;
    A.m[1][1] = 0;

    X.m[0][0] = b;
    X.m[1][0] = a;
}
