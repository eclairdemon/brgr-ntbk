#include "template.h"

/**
 * @brief Topologically sort a DAG.
 * 
 * Returns a toposort of a DAG as an array A such that
 * if A[j] is reachable from A[i], then A[i] < A[j].
 * This can also be interpreted as an assignment t of the
 * integers 0 through n-1 to the vertices of the graph
 * such that u->v if and only if t[u] < t[v]; in this case,
 * t is the inverse permutation of A.
 * 
 * @param n The number of nodes in the graph.
 * @param adj The adjacency list of the graph.
 * 
 * @return The toposort of the graph.
 */
vll toposort(ll n, vvll &adj) {
    vll ans;
    vec<bool> vis(n,0);
    auto dfs = [&](auto &&dfs, ll v) -> void {
        vis[v] = 1;
        for(ll u : adj[v]) {
            if(!vis[u]) {
                dfs(dfs,u);
            }
        }
        ans.pb(v);
    };

    for(int i = 0; i < n; i++) {
        if(!vis[i]) dfs(dfs,i);
    }
    reverse(all(ans));
    return ans;
}