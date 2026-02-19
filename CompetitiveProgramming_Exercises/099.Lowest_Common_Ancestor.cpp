// Lowest Common Ancestor
// You are given a tree with n nodes where each node has labels in the set {1,2,.......,n} .

// The tree is given as an array of edges where edges[i] = [ui, vi] is a bidirectional edge between node ui and node vi , and also you are given an array of queries where queries[i] = [ui, vi ] , you have to calculate the Lowest Common Ancestor of node ui and vi for each query.

// Return an array containing the answer of each query respectively.

// Constraints:

// 2≤ n ≤10^5

// 1<= edges.length <= n-1

// 1≤ queries.length ≤10^5



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
//     [4, 5],
//     [2, 5],
//     [1, 4]
// ]
// Output

// [3, 1, 1]

//have segmentation overflow initially due to using large array inside function.
//can use global variable or use vector and pass by reference.
#include<bits/stdc++.h>
using namespace std;

const int M=20;
void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<vector<int>>& gr){
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

int dfs_2D(int cur, int par, const vector<vector<int>>& gr, vector<vector<int>>& Par, vector<int>& dep, vector<int>& tree) {
    dep[cur] = dep[par] + 1;

    Par[cur][0] = par;
    tree[cur]++;
    for (int j = 1; j < M; j++) {
        Par[cur][j] = Par[Par[cur][j - 1]][j - 1];
    }

    for (auto x : gr[cur]) {
        if (x != par) {
            tree[cur]+=dfs_2D(x, cur, gr, Par, dep, tree);
        }
    }

    return tree[cur];
}

int LCA_2D(int u, int v, const vector<int>& dep, const vector<vector<int>>& Par) {
        
    if (u == v) return u;
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int j = M - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            // jth bit of diff is set
            u = Par[u][j];
        }
    }
    
    if(u==v){
        return u;
    }
    // u and v are on the same level
    for (int j = M - 1; j >= 0; j--) {
        if (Par[u][j] != Par[v][j]) {
            u = Par[u][j];
            v = Par[v][j];
        }
    }

    // Par[v][0]
    return Par[u][0];
}

vector<int> LCA(int n, vector<vector<int>>edges, vector<vector<int>>queries)
{
    
    vector<vector<int>> gr(n+1, vector<int>());
    vector<vector<int>> Par(n+1,vector<int>(M,0));
    vector<int> dep(n+1,0);
    vector<int> tree(n+1,0);
    
    readEdgeListIntoAdjacencyList(edges, gr);
    dfs_2D(1, 0, gr, Par, dep, tree);
    vector<int> ret;
    for(int i=0;i<queries.size();i++){
        int u=queries[i][0];
        int v=queries[i][1];
        int lca=LCA_2D(u, v, dep, Par);
        ret.push_back(lca);
    }
    return ret;
}