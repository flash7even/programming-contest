#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ff first
#define ss second
#define POPCOUNT __builtin_popcountll
#define RIGHTMOST __builtin_ctzll
#define LEFTMOST(x) (63-__builtin_clzll((x)))
#define MP make_pair
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
#define Set(N,cur) N=(N|(1<<cur))
#define Reset(N,cur) N=(N&(~(1<<cur)))
#define Check(N,cur) (!((N&(1<<cur))==0))
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)
#define nl printf("\n")
#define phl printf ("hello world\n")
#define dbgA(A,i) debug("@At pos: ",i," = ",A[i])
#define dbg(x) debug("@Print: ",x)
#define spc(N) FOR(i,0,N-1) cout<<" "
#define printArray(A,st,ed) cout<<"@Array:";FOR(i,st,ed) cout<<" "<<A[i];cout<<endl
#define LINE printf("\n"); FOR(i,0,50) printf("=");printf("\n\n")

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
int dir8[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1}};

const LL inf = 2147383647;
const LL mod = 1e9 + 7;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;
const int Size = 1000055;

///=========================  TEMPLATE ENDS HERE  ========================///
///=======================================================================///

int A[1050];
int N, LIMIT;

LL DP[110][1010][2][110][2];

/// DP[pos][sum][lc][mc][rc]:
/// pos = at which element we are.
/// sum = total cost till now.
/// lc = 1 if there is a component connected to the left border, 0 otherwise.
/// rc = 1 if there is a component connected to the right border, 0 otherwise.
/// mc = the number of component in the middle.

LL call(int pos, int sum, int lc, int mc, int rc) {
    int nSum = sum;

    if (pos > 0) {
        /// add the penalty from the last element:
        LL cnt = (lc + rc + 2*mc); /// there are cnt ways to close any component.
        nSum += cnt*(A[pos] - A[pos-1]); /// A[pos] - A[pos-1] will contribute to each of the cnt cases.
    }

    if (nSum > LIMIT) return 0;

    if (mc < 0) return 0;

    if (pos == N-1) {
        if(mc == 0) return 1;
        return 0;
    }

    if (DP[pos][sum][lc][mc][rc] != -1){
        return DP[pos][sum][lc][mc][rc];
    }

    LL res = 0;

    res += call(pos+1, nSum, 1, mc, rc); /// connect to left component
    res += call(pos+1, nSum, 1, mc-1, rc)*mc; /// connect to left component, and join to any middle component

    res += call(pos+1, nSum, lc, mc, 1); /// connect to right component
    res += call(pos+1, nSum, lc, mc-1, 1)*mc; /// connect to right component, and join to any middle component

    res += call(pos+1, nSum, lc, mc+1, rc); /// open a new middle component
    res += call(pos+1, nSum, lc, mc, rc)*mc*2; /// connect to any middle component
    res += call(pos+1, nSum, lc, mc-1, rc)*mc*(mc-1); /// join any two middle components

    return DP[pos][sum][lc][mc][rc] = res % mod;
}

int main() {
    #ifdef forthright48
    //freopen ( "input.txt", "r", stdin );
    /// freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    CLR(DP,-1);
    cin >> N >> LIMIT;
    for(int i = 0;i<N;i++) cin >> A[i];
    sort(A,A + N);
    LL res = call(0, 0, 0, 0, 0);
    cout << res << endl;
    return 0;
}
