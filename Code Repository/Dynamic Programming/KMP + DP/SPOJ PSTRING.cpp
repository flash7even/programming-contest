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

const vlong inf = 21473847;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;

///======================  TEMPLATE ENDS HERE  =====================///

const LL MOD = 1000000007;
const int Size = 10005;
#define Max 10005

char Txt[Size];
char Pat[Size];
int LPS[10005];

int patLen,txtLen;

void build_LPS_Table(){
	LPS[0] = 0;
	int j = 0;
	int i = 1;
	while(i<patLen){
		if(Pat[j] == Pat[i]){
			j++;
			LPS[i] = j;
			i++;
		}else if(j == 0){
			LPS[i] = 0;
			i++;
		}else{
			j = LPS[j-1];
		}
	}
}

int DP[10005][1005];
/// DP[i][j] = We are at i'th position of Txt and j'th position of Pat.
/// Of course the first j characters of Pat matches with Txt till now.

int FB[10005][260];
/// FB[i][j] = When we are at i'th position of Pat, what is the next fall back position k
/// such that Pat[k] = j.

int visD[10005][1005];
int visF[10005][260];

int cc = 1;

int fallBack(int cnt,char d){
    if(visF[cnt][d] == cc) return FB[cnt][d];

    int k = cnt;
    while(k>0){
        if(Pat[k] == d) break;
        k = LPS[k-1];
    }
    if(Pat[k] == d) k++;
    visF[cnt][d] = cc;
    return FB[cnt][d] = k;
}

int call(int cur,int cnt){
    if(cnt == patLen) return inf;
    if(cur == txtLen) return 0;

    if(visD[cur][cnt] == cc) return DP[cur][cnt];

    /// Remove current char:
    int res = call(cur+1,cnt) + 1;

    /// Take current char:
    if(Txt[cur] == Pat[cnt]){ /// Match found, so take it and cnt++.
        int rt = call(cur+1,cnt+1);
        res = min(res,rt);
    }else{ /// Mismatch found, so fall back to the position where match:
        int nCnt = fallBack(cnt,Txt[cur]);
        int rt = call(cur+1,nCnt);
        res = min(res,rt);
    }

    visD[cur][cnt] = cc;
    return DP[cur][cnt] = res;
}

int main () {
    //fast_cin;
    #ifdef forthright48
    freopen ( "Ainput.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif // forthright48

	while(sf("%s %s",Txt,Pat) != EOF){
		cc++;
		txtLen = strlen(Txt);
		patLen = strlen(Pat);
		build_LPS_Table();
		int res = call(0,0);
		pf("%d\n",res);
	}
    return 0;
}
