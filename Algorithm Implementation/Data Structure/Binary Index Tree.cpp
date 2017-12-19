/*
Make sure BIT is 1-indexed
1. Properly change update and read
2. Call clear() and set row and col
*/

#define Size 101000
vlong arr[Size], brr[Size];

struct BIT {

    vlong row;

    void clear( vlong r ) {
        row = r;
        CLR(arr,0);
        CLR(brr,0);
    }

    /// point update point query

    /// update(x,val) -> adds val to positions in range [x,n].
    void update ( vlong x, vlong val, vlong ar[] = arr ) {
        for ( vlong i = x; i <= row; i += i & -i ) ar[i] += val;
    }
    /// read(x) -> gets sum of elements in range [1,x].
    vlong read ( vlong x, vlong ar[] = arr ) {
        vlong res = 0;
        for ( vlong i = x; i > 0; i -= i & -i ) res += ar[i];
        return res;
    }

    /// range update point query

    /// updateRUPQ(u,v,w) -> adds w to the elements in range [u,v].
    void updateRUPQ( vlong u, vlong v, vlong w ) {
        update(u,w);
        update(v+1,-w);
        return;
    }
    /// readRUPQ(x) -> gets value at index x.
    vlong readRUPQ ( vlong x ) {
        return read(x);
    }

    /// range update range query

    /// updateRURQ(u,v,w) -> adds w to the elements in range [u,v].
    void updateRURQ( vlong u, vlong v, vlong w ) {
        update(u,w,arr);
        update(v+1,-w,arr);
        update(u,w*(u-1),brr);
        update(v+1,-w*v,brr);
    }
    /// readRURQ(x) -> gets sum of elements in range [u,v].
    vlong readRURQ( vlong u, vlong v ) {
        vlong sumv = read(v,arr) * v - read(v,brr);
        vlong sumu = read(u-1,arr) * (u-1) - read(u-1,brr);
        return sumv - sumu;
    }

    //-------------------------------------------

    int arr2D[Size][Size];
    int row, col;

    void clear2D( int r, int c ){
        row = r;
        col = c;
        CLR(arr2D,0);
    }

    /// adds val to the element at point at and beyond (x,y)
    void update2D ( int x, int y, int val ) {
        for ( int i = x; i <= row; i += i & -i ) { ///Change Here. Both increment and loop condition
            for ( int j = y; j <= col; j += j & -j ) { ///And here
                arr2D[i][j] += val;
            }
        }
    }
    /// gets sum of elements in rect[(0,0)->(x,y)]
    int read2D ( int x, int y ) {
        int res = 0;
        for ( int i = x; i > 0; i -= i & -i ) { ///Change Here. Both increment and loop condition
            for ( int j = y; j > 0; j -= j & -j ) { ///And here
                res += arr2D[i][j];
            }
        }
        return res;
    }

} bit;
