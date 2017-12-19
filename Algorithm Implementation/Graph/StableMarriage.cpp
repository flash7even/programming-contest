/// Stable Marriage Algorithm
/// Take input into prefer array (preference of each other)
/// Call stableMarriage

int N; /// Number of man/woman
int WP[Size][Size]; /// How much woman w prefer man m
int wPartner[Size]; /// Current partner of man m
int mPartner[Size]; /// Current partner of woman w
int prefer[Size][Size]; /// Preference of all people

void stableMarriage(){
    for(int w = N+1;w<=2*N;w++){
        for(int i = 1;i<=N;i++){
            int m = prefer[w][i];
            WP[w][m] = N - i;
        }
    }
    CLR(wPartner, -1);
    CLR(mPartner, -1);

    int freeMan = N;

    while (freeMan != 0){ /// All the men are still not engaged
        int m1; /// The first man in the list who is currently free.
        for (m1 = 1; m1 <= N; m1++){
            if (mPartner[m1] == -1) break;
        }
        for (int i = 1; i <= N && mPartner[m1] == -1; i++){ /// Traverse for each women till m1 is free.
            int w = prefer[m1][i];
            if (wPartner[w] == -1){ /// Current women is free. So engage m1 with w.
                wPartner[w] = m1;
                mPartner[m1] = w;
                freeMan--;
            }else {
                int m2 = wPartner[w]; /// Current women is currently engaged to m2.
                if (WP[w][m1] > WP[w][m2]){ /// Does she prefer m1 over m2?
                    wPartner[w] = m1;
                    mPartner[m1] = w;
                    mPartner[m2] = -1;
                }
            }
        }
    }
}
