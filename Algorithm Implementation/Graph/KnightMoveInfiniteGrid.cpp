/// Given the position of two knights in a infinite grid
/// Find minimum steps needed to go from one to another
LL knightDist(pii knight1, pii knight2){
    LL dx = abs(knight2.ff - knight1.ff);
    LL dy = abs(knight2.ss - knight1.ss);
    LL d = (dx+1)/2;
    d = max(d, (dy+1)/2);
    d = max(d, (dx+dy+2)/3);
    while ((d%2)!=(dx+dy)%2) d++;
    if (abs(dx) == 1 && dy == 0) return 3;
    if (abs(dy) == 1 && dx == 0) return 3;
    if (abs(dx) == 2 && abs(dy) == 2) return 4;
    return d;
}
