int DP[Size][Size];

/** FINDING LCS IN N^2 USING NESTED LOOP **/
string LCS(string str1, string str2){
    int len1 = str1.length();
    int len2 = str2.length();
    for (int i = len1 - 1; i >= 0; i--){
        for (int j = len2 - 1; j >= 0; j--){
            if (str1.at(i) == str2.at(j)){
                DP[i][j] = DP[i + 1][j + 1] + 1;
            }else{
                DP[i][j] = max(DP[i + 1][j], DP[i][j + 1]);
            }
        }
    }

    int i = 0, j = 0;
    string sb = "";
    while (i < len1 && j < len2){
        if (str1.at(i) == str2.at(j)){
            sb = sb + str1.at(i);
            i++;
            j++;
        }else if (DP[i + 1][j] >= DP[i][j + 1]){
            i++;
        }else{
            j++;
        }
    }
    return sb;
}
