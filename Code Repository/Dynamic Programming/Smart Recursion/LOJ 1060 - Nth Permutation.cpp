#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define MP make_pair
#define ff first
#define ss second
#define nl puts("")
#define sp printf(" ")
#define phl debug("Hello")
#define FOR(i,x,y) for(vlong i = (x) ; i <= (y) ; ++i)
#define ROF(i,x,y) for(vlong i = (y) ; i >= (x) ; --i)
#define CLR(x,y) memset(x,y,sizeof(x))
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((vlong)(x).size())
#define UNIQUE(V) (V).erase(unique((V).begin(),(V).end()),(V).end())
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ABS(x) ((x)<0?-(x):(x))
#define FABS(x) ((x)+eps<0?-(x):(x))
#define SQ(x) ((x)*(x))
#define LCM(x,y) (((x)/gcd((x),(y)))*(y))
#define POPCOUNT __builtin_popcountll
#define RIGHTMOST __builtin_ctzll
#define LEFTMOST(x) (63-__builtin_clzll((x)))
#define NUMDIGIT(x,y) (((vlong)(log10((x))/log10((y))))+1)
#define NORM(x) if(x>=mod) x-=mod;if(x<0) x+=mod;
#define ODD(x) (((x)&1)==0?(0):(1))
#define Set(N,p) N=((N)|((1LL)<<(p)))
#define Reset(N,p) N=((N)&(~((1LL)<<(p))))
#define Check(N,p) (!(((N)&((1LL)<<(p)))==(0)))
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)
#define arrayIndexPrint(A,i) cerr<<"~ At pos: "<<i<<" = "<<A[i]
#define dump(x) cerr<<"~ "<<#x<<" = "<<x<<endl
#define arrayPrint(A,st,ed) cerr<<"~ Array:";FOR(i,st,ed) cerr<<" "<<A[i];cerr<<endl
#define LINE cerr<<"\n"; FOR(i,0,50) cerr<<"=";cerr<<"\n\n"

#define LL long long
#define LLU long long unsigned int
typedef long long vlong;
typedef unsigned long long uvlong;
typedef pair < int, int > pii;
typedef pair < vlong, vlong > pll;
typedef vector<int> vi;
typedef vector<vlong> vl;
typedef vector<pll> vll;
//typedef tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pb_ds;

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

inline vlong gcd ( vlong a, vlong b ) {
    a = ABS ( a ); b = ABS ( b );
    while ( b ) { a = a % b; swap ( a, b ); } return a;
}

vlong ext_gcd ( vlong A, vlong B, vlong *X, vlong *Y ){
    vlong x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
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

inline vlong bigmod ( vlong a, vlong p, vlong m ) {
    vlong res = 1 % m, x = a % m;
    while ( p ) {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m; p >>= 1; /// For bigmod2 multiply here using mulmod
    }
    return res;
}


//int knightDir[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{-1,-2},{1,-2},{-2,-1} };
//int dir4[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
//int dir8[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1}};
const vlong inf = 2147383647;
const vlong mod = 1000000007;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-11;
const int Size = 50005;

///======================  TEMPLATE ENDS HERE  =====================///

#define Size 100005
#define INF (1<<30)
#define MOD 1000000007

LL fact[30];
LL cnt[30];
/// cnt[x] = number of remaining digit of x
string s;
char ans[30];
int N,K;
bool fnd = false;

/// rem = I still need to skip rem permutations
/// cur = Length of the prefix i have build till now
void call(int rem, int cur){
    if(cur == N){
        ans[cur] = '\0';
        printf("%s\n",ans);
        fnd = true;
        return;
    }
    LL psum = 0;
    /// psum = Cumulative sum of number of permutations i can make placing digit <= d at cur
    for(int d = 0;d<26;d++){
        if(fnd == true) return;
        if(cnt[d] == 0) continue;
        cnt[d]--;
        LL psbl = fact[N-cur-1];
        for(int v = 0;v<26;v++){
            psbl /= fact[cnt[v]];
        }
        /// psbl = number of permutations i can make placing d at cur
        LL tsum = psbl + psum;
        if(rem<tsum && rem>=psum){ /// I must place d at current position
            ans[cur] = ('a' + d);
            call(rem - psum,cur+1);
            if(fnd == true) return;
        }else{ /// Not enough permutation i can make if i place d here
            cnt[d]++;
            psum = tsum;
        }
    }
}

int main(){
    #ifdef forthright48
    /// freopen ( "input.txt", "r", stdin );
    /// freopen ( "output.txt", "w", stdout );
    #endif // forthright48


    fact[0] = 1;
    for(LL i = 1;i<22;i++) fact[i] = i*fact[i-1];
    int nCase;
    cin >> nCase;
    for(int cs = 1;cs<=nCase;cs++){
        cin >> s >> K;
        CLR(cnt, 0);
        N = s.length();
        for(int i = 0;i<N;i++){
            int d = (int)(s[i]-'a');
            cnt[d]++;
        }
        fnd = false;
        printf("Case %d: ",cs);
        call(K-1,0);
        if(fnd == false) printf("Impossible\n");
    }
    return 0;
}
