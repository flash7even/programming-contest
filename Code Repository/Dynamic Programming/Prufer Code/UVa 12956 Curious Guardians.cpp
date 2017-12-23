#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second
#define MP make_pair
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define POPCOUNT __builtin_popcountll
#define RIGHTMOST __builtin_ctzll
#define LEFTMOST(x) (63-__builtin_clzll((x)))
#define FOR(i,x,y) for(vlong i = (x) ; i <= (y) ; ++i)
#define ROF(i,x,y) for(vlong i = (y) ; i >= (x) ; --i)
#define CLR(x,y) memset(x,y,sizeof(x))
#define UNIQUE(V) (V).erase(unique((V).begin(),(V).end()),(V).end())
#define NUMDIGIT(x,y) (((vlong)(log10((x))/log10((y))))+1)
#define SQ(x) ((x)*(x))
#define ABS(x) ((x)<0?-(x):(x))
#define FABS(x) ((x)+eps<0?-(x):(x))
#define ALL(x) (x).begin(),(x).end()
#define LCM(x,y) (((x)/gcd((x),(y)))*(y))
#define SZ(x) ((vlong)(x).size())
#define Set(N,cur) N=(N|(1LL<<cur))
#define Reset(N,cur) N=(N&(~(1LL<<cur)))
#define Check(N,cur) (!((N&(1LL<<cur))==0))
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)
#define nl printf("\n")
#define phl cerr<<"hello\n"
#define arrayIndexPrint(A,i) cerr<<"@ At pos: "<<i<<" = "<<A[i]
#define dump(x) cerr<<"@ "<<#x<<" = "<<x<<endl
#define arrayPrint(A,st,ed) cerr<<"@ Array:";FOR(i,st,ed) cerr<<" "<<A[i];cerr<<endl
#define LINE cerr<<"\n"; FOR(i,0,50) cerr<<"=";cerr<<"\n\n"

#ifdef forthright48
     #include <ctime>
     clock_t tStart = clock();
     #define debug(args...) {dbg,args; cerr<<endl;}
     #define timeStamp debug ("Execution Time: ", (double)(clock() - tStart)/CLOCKS_PER_SEC)
     #define bug printf("%d\n",__LINE__);

#else
     #define debug(args...)  // Just strip off all debug tokens
     #define timeStamp
#endif

struct debugger{
    template<typename T> debugger& operator , (const T& v){
        cerr<<v<<" ";
        return *this;
    }
}dbg;

#define LL long long
#define LLU long long unsigned int
typedef long long vlong;
typedef unsigned long long uvlong;
typedef pair < int, int > pii;
typedef pair < vlong, vlong > pll;

inline vlong gcd ( vlong a, vlong b ) {
    a = ABS ( a ); b = ABS ( b );
    while ( b ) { a = a % b; swap ( a, b ); } return a;
}

vlong ext_gcd ( vlong A, vlong B, vlong *X, vlong *Y ){
    vlong x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0; x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1; r = r2 % r1;
        x = x2 - (q * x1); y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}

inline vlong modInv ( vlong a, vlong m ) {
    vlong x, y;
    ext_gcd( a, m, &x, &y );
    x %= m;
    if ( x < 0 ) x += m;
    return x;
}

inline vlong power ( vlong a, vlong p ) {
    vlong res = 1, x = a;
    while ( p ) {
        if ( p & 1 ) res = ( res * x );
        x = ( x * x ); p >>= 1;
    }
    return res;
}

inline vlong bigmod ( vlong a, vlong p, vlong m ) {
    vlong res = 1 % m, x = a % m;
    while ( p ) {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m; p >>= 1;
    }
    return res;
}

inline int STRLEN(char *s){
    int p = 0; while(s[p]) p++; return p;
}

//int knightDir[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{-1,-2},{1,-2},{-2,-1} };
//int dir4[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
//int dir8[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1}};

const LL inf = 1000000000;
const LL mod = 1000000007;

///=========================  TEMPLATE ENDS HERE  ========================///

const int Size = 200005;

int N, K;

LL DP[105][105];
/// DP[i][j] = In how many ways we can fill up j position using nodes from i to N
LL fact[105];

LL NCR(LL N, LL R){
    if(N<R) return 0;
    LL up = fact[N];
    LL dwn = (fact[R]*fact[N-R])%mod;
    dwn = modInv(dwn, mod);
    LL res = (up*dwn)%mod;
    return res;
}

LL call(int cur, int rem){
    if(rem<0) return 0;

    if(rem == 0) return 1;
    if(cur == N+1) return 0;

    if(DP[cur][rem] != -1) return DP[cur][rem];
    LL res = 0;
    for(int p = 0;p<=min(rem, K-1);p++){
        LL add = NCR(rem, p)*call(cur+1, rem-p);
        add %= mod;
        res = (res+add)%mod;
    }
    return DP[cur][rem] = res;
}

/// Using prufer code theory the problem reduce to this:
/// In how many ways we can build an array of length N-2
/// Where the value in each cell is between 1 to N and no values occur more than K-1 times.

int main () {
    #ifdef forthright48
    /// freopen ( "input.txt", "r", stdin );
    /// freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    fact[0] = 1;
    FOR(i,1,100) fact[i] = (fact[i-1]*i)%mod;

    while(scanf("%d %d",&N,&K) == 2){
        CLR(DP, -1);
        LL res = call(1, N-2);
        if(N == 1) res = 1;
        printf("%lld\n",res);
    }
    return 0;
}
