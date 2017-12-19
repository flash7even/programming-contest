/// Union Find Enemy vs Friends
/// Can make u and v friends or enemy
/// First call clear() to initialize.
/// Then call the required functions accordingly.

int parents[Size], n;
int MX; /// Maximum number of nodes

void clear(){
    for (int i = 0; i < Size; i++){
        parents[i] = i;
    }
}

int getParent(int a){
    if(parents[a] == a) return a;
    return parents[a] = getParent(parents[a]);
}

void unionSet(int a, int b){
    parents[getParent(a)] = getParent(b);
}

int getOpponent(int a){
    return MX - a + 1;
}

/// Returns if a and b are friends.
bool areFriends(int a, int b) {
    return (getParent(a) == getParent(b)) || (getParent(getOpponent(a)) == getParent(getOpponent(b)));
}

/// Returns if a and b are enemies.
bool areEnemies(int a, int b) {
    return (getParent(a) == getParent(getOpponent(b))) || (getParent(getOpponent(a)) == getParent(b));
}

/// Make a and b friends.
void setFriends(int a, int b) {
    unionSet(a, b);
    unionSet(getOpponent(a), getOpponent(b));
}

/// Make a and b enemies.
void setEnemies(int a, int b) {
    unionSet(a, getOpponent(b));
    unionSet(getOpponent(a), b);
}

