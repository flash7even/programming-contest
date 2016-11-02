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
#define dbgA(A,i) debug("[",i,"] = ",A[i])
#define pf printf
#define sf scanf
#define LL long long
#define LLU long long unsigned int
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)
#define pline pf("\n\n/// ================================ ///\n\n")

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

const LL MOD = 1000000007;
const int Size = 100005;

struct cell{
    int r;
    int c;
    LL val;
    cell(){
    }
    cell(int a,int b,LL v){
        r = a;c = b;val = v;
    }
};

bool cmp(cell a,cell b){
    if(a.r == b.r) return (a.c<b.c);
    return (a.r<b.r);
}

LL H,W,N;
cell bList[200005];
LL fact[2000005];

/// No of different ways to reach (r,c) from (1,1): nCr(r+c-2,c-1)

LL calc(LL r,LL c){
    LL NN = (r-1 + c-1);
    LL RR = c - 1;
    LL up = fact[NN];
    LL dwn = (fact[RR]*fact[NN-RR])%MOD;
    dwn = modInv(dwn,MOD);
    up = (up*dwn)%MOD;
    return up;
}

void solve(){
    for(int i = 0;i<N;i++){
        bList[i].val = calc(bList[i].r,bList[i].c);
    }
    for(int i = 0;i<N;i++){
        for(int j = i+1;j<N;j++){
            LL nr = bList[j].r - bList[i].r + 1;
            LL nc = bList[j].c - bList[i].c + 1;
            if(nr<0 || nc<0) continue;
            LL i2j = calc(nr,nc); /// No of ways from i to j.
            LL one2i = bList[i].val; /// No of ways from (1,1) to i.
            LL ovrLap = (i2j*one2i)%MOD; /// No of ways from (1,1) to j visiting i.
            bList[j].val -= ovrLap;
            bList[j].val = (bList[j].val + MOD)%MOD;
        }
    }
    LL res = calc(H,W);
    for(int i = 0;i<N;i++){
        LL nr = H - bList[i].r + 1;
        LL nc = W - bList[i].c + 1;
        LL i2N = calc(nr,nc); /// No of ways from i to (H,W).
        LL one2i = bList[i].val; /// No of ways from (1,1) to i without visiting any other block cell.
        LL blockPath = (i2N*one2i)%MOD; /// No of ways from (1,1) to j visiting i.
        res -= blockPath;
        res = (res + MOD)%MOD;
    }
    cout << res << endl;
}

/**
    Let's try to find the no of invalid path(Reach (H,W) from (1,1) visiting at least one block cell)
    We can remove them from the total no of ways and will get our result.
    For each block cell we have to do some calculations:
    For a block cell(r,c) we have to find the no of ways R1 to reach that cell from (1,1).
    Now let's find the no of ways R2 to reach (H,W) from (r,c).
    So the total no of ways to reach (H,W) from (1,1) visiting the block cell(r,c) is R1*R2;
    Remove it from the total answer.
**/

int main () {
    #ifdef forthright48
    //freopen ( "input.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    fact[0] = 1;
    for(LL i = 1;i<=200000;i++){
        fact[i] = (fact[i-1]*i)%MOD;
    }

    cin >> H >> W >> N;
    for(int i = 0;i<N;i++){
        cin >> bList[i].r >> bList[i].c;
    }
    sort(bList,bList+N,cmp);
    solve();
    return 0;
}
