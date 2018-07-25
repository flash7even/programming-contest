#define Max 1000000
int phi[Max];

void euler_phi(){
    phi[1] = 1;
    for(int i = 2;i<Max;i++){
        if(!phi[i]){
            phi[i] = i-1;
            for(int j = (i<<1);j<Max;j+=i){
                if(!phi[j]){
                    phi[j] = j;
                }
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}
