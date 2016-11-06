/// Include My Code Template
#include <bits/stdc++.h>
using namespace std;

int M;
string L1,L2;

map<string,int> Map;
int A[20005];
vector<int> Graph[20005];
int mark = 0;

bool topo_sort(){
	queue<int> Q;
	for(int i = 0;i<mark;i++){
		if(A[i] == 0) Q.push(i);
	}
	while(Q.empty() == false){
		int cur = Q.front();
		Q.pop();
		int Size = Graph[cur].size();
		for(int i = 0;i<Size;i++){
			int adj = Graph[cur][i];
			A[adj]--;
			if(A[adj] == 0) Q.push(adj);
		}
	}
	for(int i = 0;i<mark;i++){
		if(A[i] != 0) return false;
	}
	return true;
}

int main(){
    int nCase,u,v;
    scanf("%d",&nCase);
    for(int cs = 1;cs<=nCase;cs++){
    	scanf("%d",&M);
    	Map.clear();
    	for(int i = 0;i<20005;i++) Graph[i].clear();
    	memset(A,0,sizeof(A));
    	mark = 0;
    	for(int i = 0;i<M;i++){
    		cin >> L1 >> L2;
    		if(Map.count(L1) == 0){
    			Map[L1] = mark;
    			u = mark++;
    		}else{
    			u = Map[L1];
    		}
    		if(Map.count(L2) == 0){
				Map[L2] = mark;
				v = mark++;
			}else{
				v = Map[L2];
			}
    		Graph[u].push_back(v);
    		A[v]++;
    	}
    	bool res = topo_sort();
    	if(res == true){
    		printf("Case %d: Yes\n",cs);
    	}else{
    		printf("Case %d: No\n",cs);
    	}
    }
}
