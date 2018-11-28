vector<int> prime;

vector< pair<int,int> > primeFactorize(LL num){
    vector< pair<int,int> > flist;
    for(int i = 0;i<prime.size();i++){
        LL pf = prime[i];
        if(pf*pf>num) break;
        if(num%pf == 0){ /// pf is a prime factor of num
            int cnt = 0;
            while(num%pf == 0){ /// Find how many times num get divided by pf
                num/=pf;
                cnt++;
            }
            flist.pb(make_pair(pf, cnt));
        }
    }
    if(num>1){
        flist.pb(make_pair(num, 1));
    }
    return flist;
}
