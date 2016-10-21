#include <bits/stdc++.h>
using namespace std;

char Txt[1000005];
char Pat[1000005];
int LPS[1000005];

/// LPS[i] = maximum length of suffix from substring
/// 0 to i and is also the prefix of Pat.

int txtLen,patLen;
int cntPat = 0;

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

void run_KMP(){
	int i = 0,j = 0;
	while(i<txtLen) {
		if(Txt[i] == Pat[j]){
			i++;j++;
		}
		if(j == patLen){  /// Found a pattern;
			cntPat++;
			j = LPS[j-1];
		}else if(i<txtLen && Txt[i] != Pat[j]){
			/// If mismatch found then fall back to the
			/// previously matched prefix;
			if(j != 0){
				j = LPS[j-1];
			}else{
				i++;
			}
		}
	}
}

int main() {
	int nCase;
	scanf("%d",&nCase);
	for(int cs = 1;cs<=nCase;cs++){
		scanf("%s %s",Txt,Pat);
		txtLen = strlen(Txt);
		patLen = strlen(Pat);
		cntPat = 0;
		build_LPS_Table();
		run_KMP();
		printf("Case %d: %d\n",cs,cntPat);
	}
}
