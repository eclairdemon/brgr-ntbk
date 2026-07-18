#include "template.h"

/**
 * @brief Kosaraju's algorithm.
 * 
 * Finds SCCs in a directed graph.
 * 
 * @param n The number of nodes in the graph
 * @param adj The adjacency list of the graph
 * 
 * @return The adjacency list of the condensation graph
 */
vvll kosaraju(ll n, vvll &adj) {
    vvll components;
    vvll adj_condensed;
    vll order; // reversed toposort of G
    vec<bool> vis(n,0);

    auto dfs = [&] (auto &&dfs, ll v, vvll &adjj, vll &x) -> void {
        vis[v] = true;
        for(ll &u : adjj[v]) {
            if(!vis[u]) {
                dfs(dfs,u,adjj,x);
            }
        }
        x.pb(v);
    };

    for(int i = 0; i < n; i++) {
        if(!vis[i]) dfs(dfs,i,adj,order); 
    }

    vvll transpose(n);
    for(int v = 0; v < n; v++) {
        for(int u : adj[v]) {
            transpose[u].pb(v);
        }
    }

    vis.assign(n,0);
    reverse(order.begin(),order.end()); // regular toposort
    vll roots(n,0); // roots of SCCs
    for(ll &v : order) {
        if(!vis[v]) {
            vll comp;
            dfs(dfs,v,transpose,comp);
            components.pb(comp);
            ll root = *min_element(comp.begin(),comp.end());
            for(ll &u : comp) roots[u] = u;
        }
    }

    adj_condensed.assign(n,{});
    for(int v = 0; v < n; v++) {
        for(ll &u : adj[v]) {
            if(roots[v] != roots[u]) { // if in different SCC
                adj_condensed[roots[v]].push_back(roots[u]); // then add edge
            }
        }
    }

    return adj_condensed;
}