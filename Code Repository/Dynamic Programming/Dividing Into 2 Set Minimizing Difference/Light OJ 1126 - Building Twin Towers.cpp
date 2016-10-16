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

#define Size 100005

#define Mod 1000000007
#define Max 150000

int N;
int A[55];
int DP[2][250005];
/// DP[i][j] = Using the first i item maximum height we can make with difference j.
/// We are using row swapping technique, that's why the size of the first state is 2 not N.

int solve(int mxSum){
    CLR(DP,-1);
    DP[0][0] = 0;
    int p = 0,f = 1;
    int curSum = 0;
    /// Our goal is to maximize the total height for each difference.
    for(int i = 0;i<N;i++){
        for(int dif = 0;dif<=curSum;dif++){
            if(DP[p][dif] != -1){
                /**
                    We have already got the maximum possible height till now for keeping the difference = dif.
                    Now we have two option :
                        1. We can increase the difference to (dif + A[i]);
                        2. We can decrease the difference to (dif - A[i]);
                    by putting the current item to any of the two tower.
                **/
                int decDif = abs(dif - A[i]);
                int incDif = abs(dif + A[i]);

                if(decDif <= mxSum){ /// Putting current item to the smaller tower.
                    DP[f][decDif] = max(DP[f][decDif] , DP[p][dif] + A[i]);
                }
                if(incDif <= mxSum){ /// Putting current item to the taller tower.
                    DP[f][incDif] = max(DP[f][incDif] , DP[p][dif] + A[i]);
                }
            }
        }
        /// Merging the previous & current state,
        for(int dif = 0;dif<=curSum;dif++){
            DP[p][dif] = DP[f][dif] = max(DP[f][dif] , DP[p][dif]);
        }
        swap(p,f);
        curSum = min(curSum + A[i] , mxSum); /// Avoiding RTE
    }
    return max(DP[f][0] , DP[p][0]);
}

int main(){
    int nCase;
    sf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d",&N);
        int sum = 0;
        for(int i = 0;i<N;i++){
            sf("%d",&A[i]);
            sum += A[i];
        }
        int res = solve(sum/2);
        if(res > 0) pf("Case %d: %d\n",cs,res/2);
        else pf("Case %d: impossible\n",cs);
    }
    return 0;
}
