/// Z Algorithm
/// Z[i] = maximum length of substring that starts
/// at index i and is also the prefix of s
/// Call buildZarray()
/// Note: 0 based array

string s;
int Z[Size];

void buildZarray(int Len){
    int L = 0, R = 0;
    for(int i = 1;i<Len;i++){
        if(i>R){
            L = R = i;
            while(R<Len && s[R-L] == s[R]){
                R++;
            }
            Z[i] = R-L;
            R--;
        }else{
            int k = i - L;
            if(Z[k]<R-i+1){
                Z[i] = Z[k];
            }else{
                L = i;
                while(R<Len && s[R-L] == s[R]){
                    R++;
                }
                Z[i] = R-L;
                R--;
            }
        }
    }
    Z[0] = Len; /// Change if needs
}
