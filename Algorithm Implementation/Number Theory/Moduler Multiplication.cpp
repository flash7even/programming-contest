LL mulmod ( LL a, LL b, LL m ) {
    if ( a < b ) swap ( a, b );
    LL res = 0, x = a;
    while ( b > 0 ) {
        if ( b & 1 ) {
            res = res + x;
            if ( res >= m ) res -= m;
        }
        x = x * 2;
        if ( x >= m ) x -= m;
        b >>= 1;
     }
     return res % m;
}
