#include "template.h"

/**
 * @brief Persistent segment tree.
 * 
 * A segment tree that lets you access and modify old copies
 * by modifying the update function to return the updated branch
 * instead of modifying the current branch.
 * 
 * USAGE: forest[k] = forest[k]->update(i,x).
 */
struct Segtree {
    ll l, r;
    Segtree *lt, *rt;
    ll val;
 
    void combine() {
        val = lt->val + rt->val;
    }
 
    Segtree(ll left, ll right, vll &a) {
        l = left;
        r = right;
        lt = rt = nullptr;
        if(l == r) {
            val = a[l];
            return;
        }
        ll m = (l+r)>>1;
        lt = new Segtree(l,m,a);
        rt = new Segtree(m+1,r,a);
        combine();
    }
 
    Segtree(ll left, ll right) {
        l = left;
        r = right;
        lt = rt = nullptr;
        val = 0;
    }
 
    Segtree* update(ll i, ll x) {
        if(i < l or r < i) return this;
        Segtree* out = new Segtree(l,r);
        if(l == r and i == l) {
            out->val = x;
            return out;
        }
        out->lt = lt->update(i,x);
        out->rt = rt->update(i,x);
        out->combine();
        return out;
    }
 
    ll query(ll ql, ll qr) {
        if(qr < l or r < ql) return 0;
        if(ql <= l and r <= qr) return val;
        return lt->query(ql,qr) + rt->query(ql,qr);
    }
};