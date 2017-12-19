/// Floyd Cycle Finding Algorithm

/**
    Given a sequence of numbers or a function that find the numbers sequentially
    we need to find some informations related to cycle existence.
    1. Find if a cycle exist given the upper bound
    2. Find the length of the cycle.
    3. Find the first position when we can be assure of cycle existence.
**/

/// How many numbers we will take to find the existence of a cycle.
const LL LIMIT = 20000000;

LL A,B,C; /// Some constant needed to find next value in the sequence.

/// The function which generates the next value after x.
LL F(LL x){
    LL p1 = ((A%C) * (x%C))%C;
    LL p2 = (x%B)%C;
    return (p1 + p2)%C;
}

/// Find the information related to the cycle
/// where the first value of the sequence is st.
LL findCycle(LL st){
    LL tortoise = F(st); /// tortoise is slow :3
    LL hare = F(F(st));

    LL cnt = 0;
    while(tortoise != hare){
        cnt++;
        if(cnt>LIMIT) return -1;
        tortoise = F(tortoise);
        hare = F(F(hare));
    }

    LL M1 = 0;
    /// M1 is the first position when a cycle starts.
    LL fox = st;
    while(fox != tortoise){
        tortoise = F(tortoise);
        fox = F(fox);
        M1++;
    }

    LL M2 = 1;
    /// M2 is the length of the cycle.
    /// Basically at (M1 + M2) we first become assure of the existence of a cycle.
    /// Which started at M1.
    fox = F(tortoise);
    while(fox != tortoise){
        fox = F(fox);
        M2++;
    }

    LL cycleEnd = M1 + M2;
    if(cycleEnd > LIMIT) return -1;
    return cycleEnd;
}
