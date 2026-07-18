#include "template.h"
#include "operations.h"

/**
 * @brief A pointer-based monoidal Segment Tree.
 * 
 * Data structure to do two things on an array in O(log n) time complexity:
 * 1. Change a specific element to something else.
 * 2. Return the evaluation of an operation on some range of elements {a[l], a[l+1], ..., a[r]} (0 <= l <= r < n).
 * 
 * "Monoidal" means the operation (f) satisfies three algebraic properties:
 * 1. Closure: For all a, b in S, f(a,b) is in S.
 * 2. Associativity: For all a, b, c in S, f(f(a,b),c) == f(a,f(b,c)).
 * 3. Identity: There exists an element 'e' such that f(e,a) == f(a,e) == a.
 * 
 * A segment tree need not be monoidal; in fact, closure and associativity are enough
 * (this gives what is known as a "semigroup" instead of a monoid).
 * For simplicity, this code will use monoidal operations.
 * 
 * @param T The data type of the array, almost always just int or long long.
 * @param Op The monoid operation for the segment tree; see operations.h for examples.
 * 
 * USAGE: To declare something like a range sum segment tree on a vector a, write
 * Segtree<ll,SUM> mySegtree(0,n-1,a);
 */
template<class T, class Op>
struct Segtree {
    int l, r;
    T val;
    Segtree *lt, *rt;
    Op op;
    T ID;

    Segtree(int left, int right, const vector<T> &a, Op _op = Op())
        : l(left), r(right), lt(nullptr), rt(nullptr), op(_op), ID(Op::ID) {
        if (l == r) {
            val = a[l];
            return;
        }
        int m = (l + r) >> 1;
        lt = new Segtree(l, m, a, op);
        rt = new Segtree(m + 1, r, a, op);
        combine();
    }

    void combine() {
        val = op(lt->val, rt->val);
    }

    T query(int ql, int qr) {
        if (qr < l || r < ql) return ID;
        if (ql <= l && r <= qr) return val;
        return op(lt->query(ql, qr), rt->query(ql, qr));
    }

    void update_set(int i, T x) {
        if (i < l || r < i) return;
        if (l == r) {
            val = x;
            return;
        }
        lt->update_set(i, x);
        rt->update_set(i, x);
        combine();
    }
};
