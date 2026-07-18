#include <template.h>

/**
 * Compute the least common ancestor of two nodes in a rooted tree.
 * 
 * This uses binary lifting. The most common usage of LCA is computing
 * the distance between two nodes in a tree in O(log n) time; that function
 * is also included here, though for pure LCA you are free to omit
 * the depth array.
 * 
 * Calling dfs(0,-1) is enough to initialize all the functions here.
 * 
 * @param l ceil(log2(n)), where n is the size of the tree; usually 30 is more than enough.
 * @param up Array for binary lifting.
 * @param timer Time for ETT of the tree.
 * @param adj Adjacency list of the tree.
 * @param time_in Entry time in ETT of the tree.
 * @param time_out Exit time in ETT of the tree.
 * @param depth Depth array for the nodes of the tree.
 */
ll l = 30;
ll timer;
vvll adj, up;
vll time_in, time_out, depth;

void dfs(ll u, ll p) {
    if(p == -1) timer = 0;
    time_in[u] = ++timer;
    
    for(ll &v : adj[u]) {
        if(v==p) continue;
        dfs(v,u);

        depth[v] = 1 + depth[u];
        up[v][0] = u;

        for(int j = 1; j < l; j++) {
            if(up[v][j-1] != -1) up[v][j] = up[up[v][j-1]][j-1];
        }
    }

    time_out[u] = timer;
}

bool is_ancestor(ll u, ll v) {
    return time_in[u] <= time_in[v] and time_out[v] <= time_out[u]; 
}

ll lca(ll u, ll v) {
    if(is_ancestor(u,v)) return u;
    if(is_ancestor(v,u)) return v;
    for(int i = l-1; i >= 0; i--) {
        if(up[u][i] != -1 and !is_ancestor(up[u][i],v)) u = up[u][i];
    }
    return up[u][0];
}

ll dist(ll u, ll v) {
    return depth[u] + depth[v] - 2 * depth[lca(u,v)];
}