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
const vlong inf = 21473836470LL;
const vlong mod = 1000000007;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-11;
const int Size = 100005;

///======================  TEMPLATE ENDS HERE  =====================///

double P[3];
double DP[(2<<18)+50];
/// DP[mask] = minimum expected shot needed to shot all the target
/// when our state is mask
int vis[(2<<18)+50];
int tc = 0;

double call(int mask, int N){
	if(mask == (1<<N)-1) return 0;

	int state = mask|(1<<N);
	if(vis[state] == tc) return DP[state];
	vis[state] = tc;
	double res = inf;

    FOR(i,0,N-1){
        double cost = 0, ext = 0, k;
        FOR(s,-1,1){
            int k = i+s;
            double prob = P[s+1];
            if(k<0 || k>=N || Check(mask, k)){ /// Already got shot or out of range
                ext += prob;
                continue;
            }
            double add = 0;
            /// Whenever we find two consecutive target got shot
            /// We divide the line into two partition
            /// Because none of the partition affect the another
            if(k-1>=0 && Check(mask, k-1)){ /// right next target already got shot before
                int nmask1 = mask&((1<<k)-1);
                int nmask2 = (mask>>k)|1;
                int N1 = k, N2 = N-k;
                add += call(nmask1,N1); /// 1st partition from 0 to k-1
                add += call(nmask2,N2); /// 2nd partition from k to N-1
            }else if(k+1<N && Check(mask, k+1)){ /// left next target already got shot before
                int nmask1 = ((mask&((1<<k)-1))|(1<<k));
                int nmask2 = mask>>(k+1);
                int N1 = k+1, N2 = N-k-1;
                add += call(nmask1,N1); /// 1st partition from 0 to k
                add += call(nmask2,N2); /// 2nd partition from k+1 to N-1
            }else{
                int nmask = mask;
                Set(nmask, k);
                add += call(nmask, N); /// Shooting the k'th target for the first time
            }
            cost += add*prob;
        }
        cost += 1.0; /// Using 1 shot
        cost /= (1.0 - ext);
        /// When we shot a target which already got shot before, or when we shot outside the range
        /// Then in the next recursive call DP state doesn't change.
        /// It's like call(x) = prob*call(x) + 1;
        /// From this equation we can write: call(x) = 1/(1-prob).
        /// That's why we introduced ext and divided cost by (1-ext) at the end.
        res = min(res, cost);
    } /// right next target already got shot before
    return DP[state] = res;
}

int main() {
    #ifdef forthright48
    freopen ( "input.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    int t, N;
    scanf("%d",&t);
    FOR(cs,1,t){
        scanf("%d",&N);
        FOR(i,0,2){
            scanf("%lf",&P[i]);
            P[i]/=100.0;
        }
        tc++;
        double res = call(0, N);
        printf("%.6lf\n",res);
        debug(res);
    }

    return 0;
}
