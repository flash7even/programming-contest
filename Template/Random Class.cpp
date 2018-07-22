struct randomClass{

    const LL rndmx = 32768;

    /// Generates a random number between 1 to 2^63-1
    LL randNum(){
        LL x, y;
        x = rand()%rndmx;
        FOR(i,1,3){
            x = (x << 15);
            y = rand()%rndmx;
            x ^= y;
        }
        x = (x << 3);
        y = rand()%rndmx;
        x ^= y;
        return x;
    }

    /// Generates a random number between L to R
    LL randRangeNum(LL L, LL R){
        LL dif = (R - L)+1;
        LL x = randNum()%dif;
        return x+L;
    }

    /// Generates a random string
    string randString(int N){
        string s = "";
        FOR(i,1,N){
            LL x = randNum()%26;
            char ch = ('a'+x);
            s += ch;
        }
        return s;
    }

}rnd;
