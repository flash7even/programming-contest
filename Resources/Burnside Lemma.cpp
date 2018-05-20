/// Burnside Lemma Notes:

/**
Problem 1: Consider a circular stripe of N cells and we are given M colors.
In how many ways we can color the stripe. 2 ways are same if we can make one from other using rotation.

Here, X is a set of all colored stripes (it has M^N elements),
G is the group of its rotations (it has N elements: rotation by 0 cells, by 1 cell...by (N-1) cells),
An orbit is exactly the set of all stripes that can be obtained from each other using rotations,
So the number of orbits will be the number of distinct stripes up to a rotation.

Now let's apply the lemma, and find the number of stripes that are fixed by the rotation by K cells.
If a stripe becomes itself after rotating by K cells, then its 1st cell must have the same color as its (1+K modulo N)'th cell,
which is in turn the same as its (1+2K modulo N)'th cell...until we get back to the 1st cell again when (P*K % N)=0.

This will happen when P = N/gcd(K,N), and thus we get N/gcd(K,N) cells that must all be of the same color.
Analogously,the same amount of cells must be of the same color starting with cell 2,(2+K modulo N) etc.

Thus, all cells are separated into gcd(K,N) groups, with each group being of one color, and that yields us M^gcd(K,N) choices.
And by Burnside's lemma, the answer to the original problem is sum(M^gcd(K,N))/N, for K from 0 to N-1
**/

/**
Problem 2: You have 4 red, 4 white, and 4 blue identical dinner plates.
In how many different ways can you set a square table with one plate on each side?
2 ways are same if we can make one from other using rotation.

We have four possible rotations(clockwise) 0,90,180 and 270 degrees.
Let's A0 = rotation by 0, A1 = rotation by 90...A3 = rotation by 270 degree
So we have cyclic group of 4 elements (possible rotations)

Let's S = RWBR is a valid arrangement where R is on north, W on East, B on south and R on west
So A1(S) = RRWB(rotation by 90 degree)

Now using Burnside lemma let's find  how many arrangements are fixed under various rotations.

For A0 we rotate S by 0 degree. So there are 3^4 fixed points.

For A1 we rotate S by 90 degree. If S and A1(S) will have to be same then,
north-east must have same color, east-south must have same color,
same for south-west and west-north. Which means all side must have same color.
So there are 3 fixed points for A1.

A3 is same as A1, because rotation by 270 degree does same as rotation by 90 degree.
So there are 3 fixed points for A3 too.

For A2 we rotate S by 180 degree. If S and A2(S) will have to be same then,
north-south must have same color and east-west must have same color.
So we have 3*3 fixed points for A2.

So there are total (3^4 + 3 + 3 + 3*3) = 96 fixed points.
And by Burnside's lemma, the answer to the original problem is 96/4 = 24.
**/
