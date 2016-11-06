#include<bits/stdc++.h>
using namespace std;
#define Size 10000005

bool mark[Size];
vector <int> pL;

void seive(){
    memset (mark, true, sizeof (mark));
    mark [0] = mark [1] = false;

    for(int i = 4;i<Size;i+=2) mark [i] = false;

    for(int i=3;i*i<=Size;i+=2){
        if(mark[i]){
            for(int j=i*i;j<Size;j+=2*i)
                mark [j] = false;
        }
    }
    pL.pb (2);
    for(int i=3;i<Size;i+=2){
        if(mark[i]){
            pL.pb (i);
        }
    }
}
