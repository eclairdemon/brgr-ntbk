#include "template.h"
#include "operations.h"

/**
 * Sparse table for idempotent operators.
 * 
 * Data structure to perform idempotent associative range queries in O(1).
 * Here "idempotent" means that querying a range multiple times will not change the answer,
 * so this works for range MAX, MIN, GCD, etc.
 * 
 * @param T The data type of the sparse table, almost always int or long long.
 * @param Op The idempotent operation for the sparse table, see operations.h for examples.
 * 
 * USAGE: To declare something like a range MIN sparse table on an array a, write
 * Sparse<ll,MIN> mySparseTable(a);
 */
template<class T, class Op>
struct Sparse {
    int n, lg;
    vector<vector<T>> st;
    Op op;

    Sparse() {}

    Sparse(const vector<T> &a, Op _op = Op()) : op(_op) {
        n = (int)a.size();
        lg = 32 - __builtin_clz(n); // works for n >= 1
        st.assign(lg, vector<T>(n));
        st[0] = a;

        for (int j = 1; j < lg; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int j = 31 - __builtin_clz(r - l + 1);
        return op(st[j][l], st[j][r - (1 << j) + 1]);
    }
};