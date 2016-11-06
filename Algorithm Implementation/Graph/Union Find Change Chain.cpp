/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

/**
	3 types of operation:
	1 p q Union the sets containing p and q. If p and q are already in the same set,
	ignore this command.
	2 p q Move p to the set containing q. If p and q are already in the same set,
	ignore this command.
	3 p Return the number of elements and the sum of elements in the set containing p.
**/

const int MAXN = 100010;

int n , m;
int father[MAXN];
int sum[MAXN] , num[MAXN];

void init(){
    for(int i = 1 ; i <= n ; i++){
        father[i] = i+n;
        father[i+n] = i+n;
        sum[i+n] = i;
        num[i+n] = 1;
    }
}

int find(int x){
    if(father[x] != x){
        father[x] = find(father[x]);
	}
    return father[x];
}

int main(){
    int mark , x , y;
    while(scanf("%d%d" , &n , &m) != EOF){
         init();
         for(int i = 0 ; i < m ; i++){
             scanf("%d" , &mark);
             if(mark == 1) {
                scanf("%d%d" , &x , &y);
                int fx = find(x);
                int fy = find(y);
                if(fx != fy){
                    father[fx] = fy;
                    sum[fy] += sum[fx];
                    num[fy] += num[fx];
                }
             } else if(mark == 2) {
                scanf("%d%d" , &x , &y);
                int fx = find(x);
                int fy = find(y);
                if(fx != fy){
                   father[x] = fy;
                   sum[fy] += x;
                   sum[fx] -= x;
                   num[fy] ++;
                   num[fx] --;
                }
             } else {
                 scanf("%d" , &x);
                 int fx = find(x);
                 printf("%d %d\n" , num[fx] , sum[fx]);
             }
         }
    }
    return 0;
}
