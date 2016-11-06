//==================================================================//
// Name        : flash7even                                         //
// Author      : Tarango Khan                                       //
// Codeforces  : flash_7                                            //
// Topcoder    : flash_7                                            //
// Hackerrank  : flash_7                                            //
// Email       : tarangokhan77@gmail.com                            //
// Facebook    : tarango.khan                                       //
//==================================================================//

//==================================================================//
#include <bits/stdc++.h>                                            //
using namespace std;                                                //
#define read(nm)        freopen(nm, "r", stdin)                     //
#define write(nm)       freopen(nm, "w", stdout)                    //
#define pb              push_back                                   //
#define mp              make_pair                                   //
#define eps             1e-9                                        //
#define FABS(x)         ((x)+eps<0?-(x):(x))                        //
#define pf              printf                                      //
#define sf              scanf                                       //
#define pi              acos(-1.0)                                  //
#define SZ(x)           ((int)(x).size())                           //
#define mems(x,v)       memset(x,v,sizeof(x))                       //
#define fills(v,n)      fill(v.begin(), v.end(), n)                 //
#define vsort(v)        sort(v.begin(),v.end())                     //
#define asort(v,n)      sort(a,a+n)                                 //
#define LL              long long                                   //
#define LLU             long long unsigned int                      //
#define debug1(v1)      cout<<"1@ Debug Val 1 = "<<v1<<endl;        //
#define debug2(v2)      cout<<"   2@ Debug Num 2 = "<<v2<<endl;     //
#define debug3(v3)      cout<<"      3@ Debug Res 3 = "<<v3<<endl;  //
#define UB(v,a)   upper_bound(v.begin(),v.end(),a)-v.begin()        //
#define LB(v,a)   lower_bound(v.begin(),v.end(),a)-v.begin()        //
#define fast_cin ios_base::sync_with_stdio(false);cin.tie(NULL)     //
//==================================================================//

//==================================================================//
void make_unique(vector<int> &a){ sort(a.begin(), a.end());         //
     a.erase(unique(a.begin(), a.end()), a.end()); }                //
void printDouble(double f,int p){ cout << fixed;                    //
     cout << setprecision(p) << f <<endl; }                         //
int  Set(int N,int cur){ return N = N | (1<<cur); }                 //
int  Reset(int N,int cur){ return N = N & ~(1<<cur); }              //
bool Check(int N,int cur){ return (bool)(N & (1<<cur)); }           //
LL   GCD(LL a,LL b){ if(b == 0) return a; return GCD(b,a%b);}       //
LL   LCM(LL a,LL b){ return a*b/GCD(a,b);}                          //
LL   POW(LL a,LL p){ LL bridge_List = 1,x = a;while(p){if(p&1)              //
     bridge_List = (bridge_List*x); x = (x*x);p >>= 1;} return bridge_List;}                //
//==================================================================//

//==================================================================//
//int knightDir[8][2] = {{-2,1},{-1,2},{1,2},{2,1},                 //
//                      {2,-1},{-1,-2},{1,-2},{-2,-1}};             //
//int dir8[4][2]      = {{-1,0},{0,1},{1,0},{0,-1},                 //
//                      {-1,-1},{1,1},{1,-1},{-1,1}};               //
//int dir4[4][2]      = {{-1,0},{0,1},{1,0},{0,-1}};                //
//==================================================================//
//=======// Done With The Shortcut Stuffs! Now Let's Code! //=======//

#define Size 100

int disc[Size];
int low[Size];
int BCC_Idx[Size];
int cnt_BCC,Time;
int used[Size];
int N, M;
vector <int> Graph[Size];

stack< pair<int,int> > st;

void find_BCC(int u, int par) {
    int sz = Graph[u].size();
    pair<int,int> e, curr;
    used[u] = 1;
    disc[u] = low[u] = ++Time;
    for(int i = 0; i < sz; i++) {
        int v = Graph[u][i];
        if(v == par) continue;
        if(!used[v]) {
            st.push(mp(u, v));
            find_BCC(v, u);
            if(low[v] >= disc[u]) {
                // new component
                curr = mp(u, v);
                do {
                    e = st.top(); st.pop();
                    // e is an edge in current bcc
                } while(e != curr);
            }
            low[u] = min(low[u], low[v]);
        } else if(disc[v] < disc[u]) {
            st.push(mp(u, v));
            low[u] = min(low[u], disc[v]);
        }
    }
}

void Bioconnected_Component(){
    mems(disc, 0);
    mems(low, 0);
    mems(BCC_Idx, 0);
    mems(used,0);
    Time = cnt_BCC = 0;
    for(int i = 1; i <= N; i++){
        if(disc[i] == 0){
            find_BCC(i, -1);
        }
    }
}

void print_Graph(){
    for(int i = 1;i<=N;i++){
        int Sz = Graph[i].size();
        pf("Adj of %d:",i);
        for(int j = 0;j<Sz;j++){
            pf(" %d",Graph[i][j]);
        }
        pf("\n");
    }
}

int main(){
    int nCase,u,v;
    scanf("%d", &nCase);
    for(int cs = 1;cs<=nCase;cs++){
        sf("%d %d", &N, &M);
        for(int i = 0; i <= N; i++){
            Graph[i].clear();
        }
        res = 1;
        for(int i = 0;i<M;i++){
            sf("%d %d", &u, &v);
            Graph[u].pb(v);
            Graph[v].pb(u);
        }
        Bioconnected_Component();
        //print_Graph();
        //pf("bcc: %d\n",cnt_BCC);
        pf("Case %d: %llu\n", cs, res);
    }
    return 0;
}
