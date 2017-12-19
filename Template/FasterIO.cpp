#define gc getchar_unlocked

void readInt(int &x){
    register char c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

void readVlong (vlong &x){
    register char c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}

void readChar ( char &x ) {
    register char c = gc();
    while (c < 33) c = gc();
    x = c;
}

void readString(char *str){
    register char c = 0;
    register int i = 0;
    while (c < 33)
        c = gc();
    while (c != '\n') {
        str[i] = c;
        c = gc();
        i = i + 1;
    }
    str[i] = '\0';
}
