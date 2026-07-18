#include "template.h"

/**
 * @brief Disjoint Set Union / Union-Find
 * 
 * An data structure that allows us to dynamically
 * connect nodes and check if two nodes can
 * reach each other.
 * 
 * @param n The number of nodes in the graph.
 */
struct DSU {
    vll par, sz;

    DSU(ll n) {
        par = sz = vll(n,1);
        iota(all(par),0);
    }

    ll find(ll x) {
        return x == par[x] ? x : par[x] = find(par[x]);
    }

    bool hug(ll i, ll j) {
        if((i = find(i)) == (j = find(j))) return 0;
        if(sz[i] < sz[j]) swap(i,j);
        sz[i] += sz[j];
        par[j] = i;
    }
};