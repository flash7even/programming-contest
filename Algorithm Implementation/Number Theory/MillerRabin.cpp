vlong mulmod ( vlong a, vlong b, vlong c ) {
    if ( a < b ) swap ( a, b );
    vlong res = 0, x = a;
    while ( b > 0 ) {
        if ( b & 1 ) {
            res = res + x;
            if ( res >= c ) res -= c;
        }
        x = x * 2;
        if ( x >= c ) x -= c;
        b >>= 1;
     }
     return res % c;
}

/** Smallest odd number for which Miller-Rabin primality test on bases <= n-th prime does not reveal compositeness.
2047, 1373653, 25326001, 3215031751, 2152302898747, 3474749660383, 341550071728321, 341550071728321,
3825123056546413051, 3825123056546413051, 3825123056546413051 **/

vlong prime[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };
int psize = 13;

vlong bigmod ( vlong a, vlong p, vlong mod ) {
    vlong x = a, res = 1;
    while ( p ) {
        if ( p & 1 ) res = mulmod( res, x, mod );
        x = mulmod( x, x, mod );
        p >>= 1;
    }
    return res;
}

///Witness to compositeness of n
///n - 1 = 2^s * d, where d is odd
bool witness ( vlong a, vlong d, vlong s, vlong n ) {
    vlong r = bigmod( a, d, n );
    if ( r == 1 || r == n - 1 ) return false;
    int i;
    for ( i = 0; i < s - 1; i++ ) {
        r = mulmod( r, r, n );
        if ( r == 1 ) return true;
        if ( r == n - 1 ) return false;
    }
    return true;
}

bool Miller_Rabin ( vlong n ) {
    if ( n <= 1 ) return false;

    int i;
    vlong p = n - 1;
    vlong s = 0;
    while ( ! ( p & 1 ) ) {
        p /= 2;
        s++;
    }
    vlong d = p;
    p = n - 1;

    for ( i = 0; i < psize && prime[i] < n; i++ ) {
        if ( witness ( prime[i], d, s, n ) ) return false;
    }
    return true;
}
