#define MXL 1000005

struct KMP{
    string text, pat;
    int txtLen, patLen;
    int fail[MXL];
    /// fail[i] = maximum length of suffix at i which is also the prefix of pat

    void clear(string &t, string &p){
        text = t, pat = p;
        txtLen = SZ(text);
        patLen = SZ(pat);
    }

    void failureFunction(){
        fail[0] = 0;
        int j = 0, i = 1;
        while(i<patLen){
            if(pat[j] == pat[i]){
                j++;
                fail[i] = j;
                i++;
            }else if(j == 0){
                fail[i] = 0;
                i++;
            }else{
                j = fail[j-1];
            }
        }
    }

    void findmatching(){
        int i = 0, j = 0;
        while(i<txtLen) {
            if(text[i] == pat[j]){
                i++; j++;
                if(j == patLen){  /// Found a pattern, save and fall back
                    j = fail[j-1];
                }
            }else{
                if(j != 0){ /// Fall back
                    j = fail[j-1];
                }else{
                    i++;
                }
            }
        }
    }

}kmp;
