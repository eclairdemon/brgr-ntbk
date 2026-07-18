#include "template.h"

/**
 * @brief Segment tree on max subarray sum (Kadane)
 * 
 * It's exactly what it sounds like.
 */

struct Data {
    ll pref, suff, sum, best;
 
    Data() : pref(0), suff(0), sum(0), best(0) {}
    Data(ll a, ll b, ll c, ll d) {
        pref = a;
        suff = b;
        sum = c;
        best = d;
    }
 
    Data operator+(const Data &right) const {
        ll PREF = max({0ll, pref, sum + right.pref});
        ll SUFF = max({0ll, right.suff, right.sum + suff});
        ll SUM = sum + right.sum;
        ll BEST = max({best, right.best, right.pref + suff});
        return Data(PREF, SUFF, SUM, BEST);
    }
};
 
const Data ident = Data(0,0,0,0);
 
struct Segtree {
    ll l, r;
    Segtree *lt, *rt;
    Data data;
 
    void combine() {
        data = lt->data + rt->data;
    }
 
    Segtree(ll left, ll right, vll &a) {
        l = left;
        r = right;
        lt = rt = nullptr;
        if(l == r) {
            data = Data(max(0ll, a[l]),max(0ll, a[l]),a[l],max(0ll, a[l]));
            return;
        }
        ll m = (l+r)>>1;
        lt = new Segtree(l,m,a);
        rt = new Segtree(m+1,r,a);
        combine();
    }

    void update(ll i, ll x) {
        if(i < l or r < i) return;
        if(l==r and i==l) {
            data = Data(max(0ll,x),max(0ll,x),x,max(0ll,x));
            return;
        }
        lt->update(i,x);
        rt->update(i,x);
        return;
    }
 
    Data query(ll ql, ll qr) {
        if(qr < l or r < ql) return ident;
        if(ql <= l and r <= qr) return data;
        return lt->query(ql,qr) + rt->query(ql,qr);
    }
};