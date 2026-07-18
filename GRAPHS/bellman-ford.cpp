#include "template.h"

/**
 * @brief Find the shortest distance between a start node and all other nodes in a weighted graph.
 * 
 * Unlike Dijkstra's Algorithm this works for negative edge weights,
 * and can also be used to detect a negative cycle.
 * This comes at the cost of O(VE) time complexity.
 * 
 * @param n The number of nodes in the graph.
 * @param start The start node of the graph
 * @param edges The edges in the graph; note these are stored as [w,u,v] where w is the weight of the edge from u to v.
 * 
 * @return The distance array, where dist[v] is the distance from the start node to node v, OR {-1} in the case of a negative cycle.
 */
vll bellman_ford(ll n, ll start, vec<array<ll,3>>&edges) { // returns {-1} in case of negative cycle
    vll dist(n,1e18);
    dist[start] = 0;

    for(int i = 0; i < n; i++) {
        for(auto &[w,u,v] : edges) {
            if(dist[u] != 1e18 and dist[u] + w < dist[v]) {
                if(i == n-1) return {-1};
                dist[v] = dist[u] + w;
            }
        }
    }

    return dist;
}