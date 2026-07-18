#include "template.h"

/**
 * @brief Find the shortest distance between all pairs of nodes in a graph.
 * 
 * Does what you expect. This runs in O(V^3).
 * This works with negative edge weights but does not output
 * anything useful in the case of a negative cycle.
 * 
 * @param n The number of nodes in the graph.
 * @param adj The adjacency list of the graph.
 * 
 * @return The distance array, where dist[u][v] is the shortest distance between u and v.
 */
vvll floyd_warshall(ll n, vec<vec<pll>>& adj) {
    vvll dist(n, vll(n,1e18));
    for(int u = 0; u < n; u++) {
        dist[u][u] = 0;
        for(auto &[v,w] : adj[u]) {
            dist[u][v] = w;
        }
    }

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(dist[i][k] != 1e18 and dist[k][j] != 1e18) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}