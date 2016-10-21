#include <bits/stdc++.h>
using namespace std;

/// Barnestaine String Hashing:

LLU hash(const char* s) {
    LLU hash = 0, c;
    while((c = *s++)){
    	hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

LLU hash(string s) {
    LLU hash = 0, c;
	int Len = s.length();
    for(int i = 0;i<Len;i++){
		c = (LLU)(s[i]);
    	hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}
