#include "template.h"

/**
 * @brief Fast doubling to compute Fibonacci numbers.
 * 
 * Computes the pair {F_n, F_(n+1)} in O(log n) time and small constant.
 * We use the convention F_0 = 0, F_1 = 1.
 * 
 * @param n The Fibonacci index to find.
 * @param m The modulo.
 * 
 * @return The pair {F_n, F_(n+1)}.
 */
pll fast_doubling(ll n, ll m = MOD) {
    if(n==0) return {0,1};

    pll p = fast_doubling(n >> 1, m);
    ll c = (p.fi * ((2 * p.se - p.fi + m) % m)) % m;
    ll d = ((p.se * p.se) % m + (p.fi * p.fi) % m) % m;
    
    return (n & 1) ? make_pair(d, (c+d)%m) : make_pair(c,d);
}