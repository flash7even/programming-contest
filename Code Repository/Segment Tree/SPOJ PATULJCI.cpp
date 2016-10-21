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
const int Size = 300005;

/**
    Let's make a sequence including all the elements in the range. Now build the algorithm like this:

    "while there are different numbers in the sequence select
     any two different numbers from the sequence and erase them"

    For example if the sequence were:
    1 2 3 1 2 3 2 3
    The algorithm could have done this:
    1 2 3 1 2 3 2 3 --> 3 1 2 3 2 3 -> 1 3 2 3 -> 3 3

    Note that we could also end up with other sequences if we selected pairs in a different way.

    Let candidate be the number that is left in a sequence (3 in the example above).
    Let count be the number of numbers left in a sequence (2 in the example above).

    The cool thing about the algorithm is that if there is a number that appears more than N/2
    times in the sequence it must end up as a candidate no matter the way we select pairs.
    Intuitively, we don't have enough other numbers to kill all of the
    candidate numbers. So we can choose our own way to select the pairs.

    Note that, the last number we found may not be the result always because number of count of it may be smaller than half.
    But if there exists a result then definitely this number'll be that result.

    We can check the number of occurrence of that number using binary search, building a vector array on positions.

    Idea Credit : http://spoj-solutions.blogspot.com/2015/10/patuljci-snow-white-and-n-dwarfs.html
**/

struct vert{
	int mxCol;
	int cnt;
};

int N,Q;
vert T[Size*4];
int A[Size];

vert mrg(vert L,vert R){
    vert rs;
    if(L.mxCol == R.mxCol){
        rs.mxCol = L.mxCol;
        rs.cnt = L.cnt + R.cnt;
    }else if(L.cnt>R.cnt){
        rs.mxCol = L.mxCol;
        rs.cnt = L.cnt - R.cnt;
    }else{
        rs.mxCol = R.mxCol;
        rs.cnt = R.cnt - L.cnt;
    }
    return rs;
}

void bT(int cur,int s,int e){
    if(s == e){
        T[cur].mxCol = A[s];
        T[cur].cnt = 1;
        return;
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    bT(L,s,M);
    bT(R,M+1,e);
    T[cur] = mrg(T[L],T[R]);
}

vert qT(int cur,int s,int e,int u,int v){
    vert vv;
    if(e < u || s > v){
        return vv;
    }
    if(s >= u && e <= v){
        return T[cur];
    }
    int L = cur*2,R = cur*2+1,M = (s+e)/2;

    if(M >= v){
        return qT(L,s,M,u,v);
    }else if(M<u){
        return qT(R,M+1,e,u,v);
    }else{
        vert v1 = qT(L,s,M,u,v);
        vert v2 = qT(R,M+1,e,u,v);
        return mrg(v1,v2);
    }
}

vector<int> POS[100005];

int main () {
    #ifdef forthright48
    freopen ( "Ainput.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

    int u,v,K;
    sf("%d %d",&N,&K);
    for(int i = 1;i<=N;i++){
        sf("%d",&A[i]);
        POS[A[i]].pb(i);
    }
    sf("%d",&Q);
    bT(1,1,N);
    for(int i = 1;i<=Q;i++){
        sf("%d %d",&u,&v);
        vert rs = qT(1,1,N,u,v);
        if(rs.cnt>0){
            int res = (upper_bound(POS[rs.mxCol].begin(),POS[rs.mxCol].end(),v) - lower_bound(POS[rs.mxCol].begin(),POS[rs.mxCol].end(),u));
            if(res > (v-u+1)/2){
                pf("yes %d\n",rs.mxCol);
            }else{
                pf("no\n");
            }
        }else{
            pf("no\n");
        }
    }
    return 0;
}
