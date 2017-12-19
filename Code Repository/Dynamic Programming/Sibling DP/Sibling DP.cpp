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
const LL inf = 2147383647LL;
const LL mod = 1e9 + 7; /// CHANGE HERE
const int Size = 200005; /// CHANGE HERE

///=========================  TEMPLATE ENDS HERE  ========================///

/// Problem Link: http://codeforces.com/contest/855/problem/C
/// Idea: Sibling DP

int N, M, K, X;
vector<int> Graph[Size];
int sibling[Size];
int child[Size];
LL DP[Size][11][3];
/// DP[u][cnt][f] means:
/// u = which node
/// cnt = number of remaining special node to fill
/// f = if my parent value is <, = or > than K

void DFS(int u, int p){
    bool leaf = true;
    int v1 = -1;
    for(int i = 0;i<Graph[u].size();i++){
        int v2 = Graph[u][i];
        if(v2 == p) continue;
        DFS(v2, u);
        if(leaf == true){
            child[u] = v2;
            v1 = v2;
        }else{
            sibling[v1] = v2;
        }
        v1 = v2;
        leaf = false;
    }
}

LL call(int u, int rem, int f){
    if(DP[u][rem][f] != -1) return DP[u][rem][f];
    int bro = sibling[u], son = child[u];
    LL res = 0, ret, v1;

    if(son == -1 && bro == -1){ ///  Base case
        if(f == 0){
            if(rem == 0) res = M-1;
            else if(rem == 1) res = 1;
        }else if(f == 1){
            if(rem == 0) res = K-1;
        }else{
            if(rem == 0) res = M-1;
        }
        return res;
    }

    if(son == -1){
        LL r1, r2;
        /// Place a color > k at u
        if(f != 1){ /// Parent value != K
            ret = call(bro, rem, f);
            ret = (ret*(M-K))%mod; /// There are (M-K) possible big color
            res = (res + ret)%mod;
        }
        /// Place a color < k at u
        ret = call(bro, rem, f);
        ret = (ret*(K-1))%mod; /// There are (K-1) possible small color
        res = (res + ret)%mod;

        /// Now place color k at u
        if(f == 0 && rem>0){ /// Parent value < K
            ret = call(bro, rem-1, f);
            res = (res + ret)%mod;
        }
    }else if(bro == -1){
        LL r1, r2;
        /// Place a color > k at u
        if(f != 1){ /// Parent value != K
            ret = call(son, rem, 2);
            ret = (ret*(M-K))%mod; /// There are (M-K) possible big color
            res = (res + ret)%mod;
        }
        /// Place a color < k at u
        ret = call(son, rem, 0);
        ret = (ret*(K-1))%mod; /// There are (K-1) possible small color
        res = (res + ret)%mod;

        /// Now place color k at u
        if(f == 0 && rem>0){ /// Parent value < K
            ret = call(son, rem-1, 1);
            res = (res + ret)%mod;
        }
    }else{
        for(int a = 0;a<=rem;a++){
            int b = rem - a;
            LL r1, r2;
            /// Place a color > k at u
            if(f != 1){ /// Parent value != K
                r1 = call(son, a, 2);
                r2 = call(bro, b, f);
                ret = (r1*r2)%mod;
                ret = (ret*(M-K))%mod; /// There are (M-K) possible big color
                res = (res + ret)%mod;
            }
            /// Place a color < k at u
            r1 = call(son, a, 0);
            r2 = call(bro, b, f);
            ret = (r1*r2)%mod;
            ret = (ret*(K-1))%mod; /// There are (K-1) possible small color
            res = (res + ret)%mod;
        }

        /// Now place color k at u
        for(int a = 0;a<=rem-1;a++){
            int b = (rem-1) - a;
            LL r1, r2;
            if(f == 0){ /// Parent value < K
                r1 = call(son, a, 1);
                r2 = call(bro, b, f);
                ret = (r1*r2)%mod;
                res = (res + ret)%mod;
            }
        }
    }
    return DP[u][rem][f] = res;
}

int main () {
    #ifdef forthright48
    freopen ( "input.txt", "r", stdin );
    /// freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    scanf("%d %d",&N,&M);
    for(int i = 0;i<N-1;i++){
        int u, v;
        scanf("%d %d",&u,&v);
        Graph[u].pb(v);
        Graph[v].pb(u);
    }
    scanf("%d %d",&K,&X);
    CLR(child, -1);
    CLR(sibling, -1);
    CLR(DP, -1);
    DFS(1, 1);
    LL res = 0;

    for(int rem = X;rem>=0;rem--){
        LL ret = call(1, rem, 0);
        res = (res + ret)%mod;
    }
    cout << res << endl;

    return 0;
}
