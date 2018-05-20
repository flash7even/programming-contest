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

const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;
const LL inf = 2147383LL;
const LL mod = 1e9 + 7; /// CHANGE HERE
const int Size = 105; /// CHANGE HERE

///=========================  TEMPLATE ENDS HERE  ========================///

int N, K;
vector<int> Graph[Size];
vector<int> Cost[Size];

LL DP[105][105];
/// DP[u][k]: u = current node, k = remaining values we can use
/// DP[u][k] = minimum communities we can divided into

int vis[105][105];
int tc = 0;

/// Call function returns the minimum cost when
/// we are at idx'th child of p, whose parent is pp and
/// we have rem remaining values left

int call(int p, int idx, int pp, int rem){
    if(idx == Graph[p].size()) return 0;
    int u = Graph[p][idx];
    if(u == pp) return call(p, idx+1, pp, rem);
    if(vis[u][rem] == tc) return DP[u][rem];
    vis[u][rem] = tc;

    /// Choice 1: Leave the current child to new component and continue with sibling
    int res = call(u, 0, p, K) + 1 + call(p, idx+1, pp, rem);

    /// Choice 2: Connect with current child and continue with sibling
    int nrem = rem - Cost[p][idx];
    if(nrem>=0){
        FOR(i,0,nrem){
            int ret = call(u, 0, p, i) + call(p, idx+1, pp, nrem-i);
            res = min(res, ret);
        }
    }
    return DP[u][rem] = res;
}

int main () {
    #ifdef forthright48
    freopen ( "input.txt", "r", stdin );
    /// freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    int nCase;
    scanf("%d",&nCase);
    FOR(cs,1,nCase){
        tc++;
        scanf("%d %d",&N,&K);
        FOR(i,0,N){
            Graph[i].clear();
            Cost[i].clear();
        }
        FOR(i, 0, N-2){
            int u, v, w;
            scanf("%d %d %d",&u,&v,&w);
            Graph[u].pb(v);
            Graph[v].pb(u);
            Cost[u].pb(w);
            Cost[v].pb(w);
        }
        int res = call(1, 0, -1, K) + 1;
        printf("Case %lld: %d\n",cs,res);
    }

    return 0;
}
