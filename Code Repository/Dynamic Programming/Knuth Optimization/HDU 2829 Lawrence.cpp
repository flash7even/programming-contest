///==================================================================//
/// Problem     : Contest Code                                       //
/// Author      : NSU Aristocrats                                    //
/// Represents  : North South University                             //
/// Email       : nsu3aristocrats@gmail.com                          //
/// Codeforces  : http://codeforces.com/team/21235                   //
/// Verdict     : In Queue                                           //
/// Date        : 02/10/2016                                         //
///==================================================================//

///====================== TEMPLATE STARTS HERE =====================///
//#include <bits/stdc++.h>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<vector>
#include<deque>
#include<functional>
#include<string>
#include<iostream>
#include<cctype>
#include<set>
#include<climits>
#include<iomanip>
#include<cassert>
#include<sstream>

#define pb push_back
#define nl puts ("")
#define sp printf ( " " )
#define phl printf ( "hello\n" )
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
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define NUMDIGIT(x,y) (((vlong)(log10((x))/log10((y))))+1)
#define SQ(x) ((x)*(x))
#define ABS(x) ((x)<0?-(x):(x))
#define FABS(x) ((x)+eps<0?-(x):(x))
#define ALL(x) (x).begin(),(x).end()
#define LCM(x,y) (((x)/gcd((x),(y)))*(y))
#define SZ(x) ((vlong)(x).size())
#define NORM(x) if(x>=mod)x-=mod;
#define MOD(x,y) (((x)*(y))%mod)
#define ODD(x) (((x)&1)==0?(0):(1))
#define dbgA(A,i) debug("[",i,"] = ",A[i]);
#define inpI(x) sf("%d",&x)
#define inpL(x) sf("%lld",&x)
#define inpD(x) sf("%lf",&x)
#define pf printf
#define sf scanf
#define LL long long
#define LLU long long unsigned int
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;

typedef long long vlong;
typedef unsigned long long uvlong;
typedef pair < vlong, vlong > pll;
typedef pair < int, int > pii;
typedef vector<pll> vll;
typedef vector<vlong> vl;

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

//int knightDir[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{-1,-2},{1,-2},{-2,-1} };
//int dir4[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
//int dir8[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{1,1},{1,-1},{-1,1}};

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

int  Set(int N,int cur){ return N = N | (1<<cur); }
int  Reset(int N,int cur){ return N = N & ~(1<<cur); }
bool Check(int N,int cur){ return (bool)(N & (1<<cur)); }

const vlong inf = 2147383647;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;

///======================  TEMPLATE ENDS HERE  =====================///

/**
    The problem can be easily solved by old fashioned DP approach.
    But the complexity will become N^2*M which'll get TLE.
    Notice here, we don't need to run the middle loop for each interval.
    There is a quadrangle inequality here which satisfy knuth's conditions.
    So we can apply Knuth's optimization.
    Link : https://www.quora.com/What-is-Knuths-optimization-in-dynamic-programming
**/

#define Size 1005

int N,M;
int A[Size];
int mid[Size][Size];
int DP[Size][Size];
/// DP[i][k] = Minimum total cost to divide first i positions into k partitions.
/// Where the k'th partition is at position i.
int cost[Size][Size]; /// cost[i][j] = cost of the partiton i - j.
int csum[Size];

/// Knuth's Conditions:
/// mid[i,j-1] <= mid[i,j] <= mid[i+1,j]
/// Here, mid[i][j] = k represents the index which gives the optimal answer if we make a partition at k.
/// cost[i][j] represents the cost for the interval i to j.
/// For any a,b,c,d where a <= b <= c <= d :
/// cost[a][c] + cost[b][d] <= cost[a][d] + cost[b][c] (quadrangle inequality).
/// cost[b][c] <= cost[a][d] (monotonicity).

void costFunc(){
    FOR(i,1,N){
        csum[i] = A[i];
        cost[i][i] = 0;
        FOR(j,i+1,N){
            csum[j] = csum[j-1] + A[j];
            cost[i][j] = cost[i][j-1] + csum[j-1]*A[j];
        }
    }
}

int solve(){
    costFunc();
    FOR(k,1,M){
        mid[N+1][k] = N;
    }

    FOR(i,1,N){
        DP[i][1] = cost[1][i];
        mid[i][1] = 0;
    }

    for (int k = 2; k <= M; k++){
        for (int i = N; i >= 1; i--) {
            int L1 = mid[i][k-1];
            int L2 = mid[i+1][k];
            DP[i][k] = inf;
            /// The optimal answer lie for an index between (L1 - L2).
            /// So we don't need to check for all (1 - i) to make a partition.
            for(int m = L1;m<=L2 && m<i;m++){
                int rs = DP[m][k-1] + cost[m+1][i];
                if(rs < DP[i][k]){
                    DP[i][k] = rs;
                    mid[i][k] = m;
                }
            }
        }
    }
    return DP[N][M];
}

int main () {
    #ifdef forthright48
    freopen ( "input.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    while(sf("%d %d",&N,&M) == 2){
        if(N == 0 && M == 0) break;
        M++;
        FOR(i,1,N){
            inpI(A[i]);
        }
        int res = solve();
        pf("%d\n",res);
    }
    return 0;
}
