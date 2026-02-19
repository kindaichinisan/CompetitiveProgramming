// Distance Queries
// You are given a tree consisting of n nodes, each node has labels in the set {1,2,.......,n} .

// The tree is given as an array of edges where edges[i] = [ui , vi] is a bidirectional edge between node ui and node vi , and also you are given an array of queries where queries[i] = [ui, vi ] , you have to calculate the distance between node ui and vi in each query.

// Return an array containing the answer of each query respectively.

// Constraints:

// 2≤ n ≤10^5

// 1<= edges.length <= n-1

// 1≤ queries.length ≤10^5

// 1<= ui, vi <=n



// Example:

// Input

// n = 5 
// edges = [
//     [1, 2],
//     [1, 3],
//     [3, 4],
//     [3, 5]
// ]
 
// queries = [
//     [1, 3],
//     [2, 5],
//     [1, 4]
// ]
// Output

// [1, 3, 2]

#include<bits/stdc++.h>
using namespace std;

void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<vector<int>>& gr){
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

int dfs_1D(int cur, int par, const vector<vector<int>>& gr, vector<int>& Par, vector<int>& dep, vector<int>& tree) {
    dep[cur] = dep[par] + 1;
    Par[cur] = par;
    tree[cur]=1;
    for (auto x : gr[cur]) {
        if (x != par) {
            // x is child node
            tree[cur]+=dfs_1D(x, cur, gr, Par, dep, tree);
        }
    }
    
    return tree[cur];
}

int LCA_1D(int u, int v, const vector<int>& dep, const vector<int>& Par) {
    if (u == v) return u;

    if (dep[u] < dep[v]) swap(u, v);
    // depth of u is more than depth of v

    int diff = dep[u] - dep[v];

    // depth of both nodes same
    while (diff--) {
        u = Par[u];
    }

    // until they are equal nodes keep climbing
    while (u != v) {
        u = Par[u];
        v = Par[v];
    }

    return u;
}


vector<int> distanceQuery(int n, vector<vector<int>>edges, vector<vector<int>>queries)
{
    vector<vector<int>> gr(n+1, vector<int>());
    vector<int> Par(n+1, 0);
    vector<int> dep(n+1,0);
    vector<int> tree(n+1,0);
    readEdgeListIntoAdjacencyList(edges, gr);
    dfs_1D(1, 0, gr, Par, dep, tree);
    vector<int> ret;
    for(int i=0;i<queries.size();i++){
        int u=queries[i][0];
        int v=queries[i][1];
        int lca=LCA_1D(u, v, dep, Par);
        int dist=dep[u]+dep[v]-2*dep[lca];
        ret.push_back(dist);
    }
    return ret;
}