#include "template.h"


/**
 * @brief Find the shortest distance between a start node and all other nodes in a weighted graph.
 * 
 * This runs in O((V+E)log V).
 * This does not work if the graph has negative edge weights!
 * In that case you must use Bellman-Ford.
 * 
 * @param n The number of nodes in the graph
 * @param start The starting node
 * @param adj The adjacency list of the graph
 * 
 * @return The distance array, where dist[v] is the distance from the start node to v.
 */
vll dijkstras(ll n, vec<vec<pll>> &adj, ll start) {
    priority_queue<pll, vec<pll>, greater<pll>> pq;
    pq.push({0,start});

    vll dist(n,1e18);
    dist[start] = 0;

    while(!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto &[v,w] : adj[u]) {
            if(dist[v] > w + d) {
                dist[v] = w + d;
                pq.push({dist[v],v});
            }
        }
    }

    return dist;
}