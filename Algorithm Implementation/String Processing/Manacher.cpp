#define MANALEN 200100
/// Warning: Make MANALEN double of string length

/**
1. First assign string to manacher, arr[]
2. Call init
3. Call Preprocess to convert string
4. Call calc to calculate array p[]
**/

struct MANACHER {
    char arr[MANALEN+10], brr[MANALEN+10];
    int p[MANALEN+10];
    int an, bn, mxpalin, mxcenter;

    void init() {
        //Assign string to arr
        an = strlen ( arr );
    }

    //aba -> ^#a#b#a#$
    void preprocess() {
        int cur = 0;
        brr[cur++] = '^';
        FOR(i,0,an-1) {
            brr[cur++] = '#';
            brr[cur++] = arr[i];
        }
        brr[cur++] = '#';
        brr[cur++] = '$';
        brr[cur] = 0;
        bn = cur;
    }

    ///For each possible center, length of palindrome it can create.
    ///Careful, this length is without #
    void calc() {
        int c = 0, r = 0;
        FOR(i,1,bn-2) {
            int mi = c - (i-c);

            p[i] = (r > i )? MIN ( r - i, p[mi] ): 0;

            while ( brr[i+p[i]+1] == brr[i-p[i]-1] ) {
                p[i]++;
            }

            if ( i + p[i] > r ) {
                r = i + p[i];
                c = i;
            }
        }

        mxpalin = 0; mxcenter = 0;
        ///Notice we don't multiply 2 with p[i], cause more than half of them are #
        FOR(i,1,bn-2) {
            if ( p[i] > mxpalin ) {
                mxpalin = p[i];
                mxcenter = i;
            }
        }
        ///In brr[], for each center, the palindrome extends from i-p[i] to i+p[i]
    }
}mana;
