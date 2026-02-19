// Path Xor
// You are given a tree with n nodes where each node i has ai value.

// The tree is given as an array of edges where edges[i] = [ui, vi] is a bidirectional edge between node ui and node vi , and also you are given an array of queries where queries[i] = [ui, vi ] , you have to calculate the  XOR of value of nodes on the shortest path from node ui to vi for each query.

// Return an array containing the answer of each query respectively.

// Constraints:

// 3≤ n ≤10^5

// 2<= edges.length <= n-1

// 1≤ queries.length ≤10^5

// 1≤ ai ≤10^8

// 1<= ui, vi <=n



// Example:

// Input

// n = 5 , a =[1, 2, 3, 4, 5]
// edges = [
//     [1, 2],
//     [1, 3],
//     [2, 4],
//     [2, 5]
// ]
 
// queries = [
//     [3, 5],
//     [4, 5]
// ]
// Output

// [5, 3]
// Explanation

// The path for (3,5) is :
// 3 → 1 → 2 → 5; therefore, the answer for the query is 5.
// The path for (4,5) is :
// 4 → 2 → 5; therefore, the answer for the query is 3.

#include<bits/stdc++.h>
using namespace std;

const int N=100005;

void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<int> gr[N]){
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}


int dfs_1D(int cur, int par, vector<int> gr[N], int Par[N], int dep[N], int tree[N], const vector<int>& a, int xor_vle[N]) {
    dep[cur] = dep[par] + 1;
    Par[cur] = par;
    tree[cur]=1;
    xor_vle[cur]=xor_vle[par] ^ a[cur-1];
    for (auto x : gr[cur]) {
        if (x != par) {
            // x is child node
            tree[cur]+=dfs_1D(x, cur, gr, Par, dep, tree, a, xor_vle);
        }
    }
    
    return tree[cur];
}

int LCA_1D(int u, int v, int dep[N], int Par[N]) {
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

vector<int> pathXor(int n, vector<int> a, vector<vector<int>> edges, vector<vector<int>> queries){
    
    vector<int> gr[N];
    int Par[N];
    int tree[N];
    int dep[N];
    int xor_vle[N];
    memset(tree, 0, sizeof(tree));
    memset(xor_vle, 0, sizeof(xor_vle));
    dep[0]=0;
    xor_vle[0]=0;
    readEdgeListIntoAdjacencyList(edges, gr);
    dfs_1D(1, 0, gr, Par, dep, tree, a, xor_vle);
    vector<int> ret;
    for(int i=0;i<queries.size();i++){
        int u=queries[i][0];
        int v=queries[i][1];
        int lca=LCA_1D(u, v, dep, Par);
        int vle=xor_vle[u] ^ xor_vle[v] ^ a[lca-1];
        ret.push_back(vle);
    }
    return ret;
}