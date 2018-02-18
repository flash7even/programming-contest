char Txt[1000005];
char Pat[1000005];
int LPS[1000005];

/// LPS[i] = maximum length of suffix from substring
/// 0 to i which is also the prefix of Pat.

int txtLen; /// Text length
int patLen; /// Pattern length
int cntPat = 0; /// Number of times the pattern matched

void failureFunction(){
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

void KMP(){
    failureFunction();
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
