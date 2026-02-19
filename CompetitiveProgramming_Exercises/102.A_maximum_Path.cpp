// A maximum Path
// You are given an undirected Tree with n nodes rooted at node 1 , every ith node is assigned a value denoted by ai .

// The tree is given as an array of edges where edges[i] = [ui, vi] is a bidirectional edge between node ui and node vi , and also you are given an array of queries where queries[i] = [ui, vi ] , you have to calculate the maximum value of the node present  on a simple path from node ui to vi for each query.

// Return an array containing the answer of each query respectively.

// Constraints:

// 3≤ n ≤10^5

// 2<= edges.length <= n-1

// 1≤ queries.length ≤10^5

// 1≤ ai ≤10^9

// 1<= ui, vi <=n



// Example:

// Input

// n = 5 , a =[5, 2, 4, 2, 6]
// edges = [
//     [1, 2],
//     [2, 3],
//     [1, 4],
//     [3, 5]
// ]
 
// queries = [
//     [1, 4],
//     [2, 5]
// ]
// Output

// [5, 6]
// Explanation

// For Query 1:
// Simple path between node 1 and 4 is 1−4. Maximum value of node present on simple path is 5 which is value of node 1.
 
// For Query 2:
// Simple path between node 2 and 5 is 2−3−5. Maximum value of node present on simple path is 6 which is value of node 5.

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

int dfs_2D(int cur, int par, const vector<vector<int>>& gr, vector<vector<int>>& Par, vector<int>& dep, vector<int>& tree, vector<vector<int>>& max_vle, const vector<int>& a) {
    dep[cur] = dep[par] + 1;

    Par[cur][0] = par; //immediate parent
    max_vle[cur][0]=max(a[cur-1], a[par-1]); //max of its own vle and immediate parent vle
    tree[cur]=1;
    for (int j = 1; j < M; j++) {
        Par[cur][j] = Par[Par[cur][j - 1]][j - 1]; //its immediate parent's immediate parent
        max_vle[cur][j] = max(max_vle[cur][j-1], max_vle[Par[cur][j - 1]][j-1]);
    }

    for (auto x : gr[cur]) {
        if (x != par) {
            tree[cur]+=dfs_2D(x, cur, gr, Par, dep, tree, max_vle, a);
        }
    }

    return tree[cur];
}

int LCA_2D(int u, int v, const vector<int>& dep, const vector<vector<int>>& Par, const vector<vector<int>>& max_vle, const vector<int>& a) {
        
    if (u == v) return a[u-1];
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    int maxi=max(a[u-1],a[v-1]);
    for (int j = M - 1; j >= 0; j--) {
        if ((diff >> j) & 1) {
            // jth bit of diff is set
            maxi=max(maxi, max_vle[u][j]);
            u = Par[u][j];
        }
    }
    
    if(u==v){
        return max(maxi, a[u-1]);
    }
    // u and v are on the same level
    for (int j = M - 1; j >= 0; j--) {
        if (Par[u][j] != Par[v][j]) {
            maxi=max(maxi, max_vle[u][j]);
            maxi=max(maxi, max_vle[v][j]);
            u = Par[u][j];
            v = Par[v][j];
        }
    }

    // Par[v][0]
    return max(maxi, a[Par[u][0]-1]);
}

void printEdgeList(const vector<vector<int>>& edges){
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        cout<<u<<" "<<v<<endl;
    }
}

vector<int> maximumPath (int n, vector<int> a, vector<vector<int>> edges, vector<vector<int>> queries)
{
    printEdgeList(edges);
    for(int i=0;i<a.size();i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    vector<vector<int>> gr(n+1, vector<int>());
    vector<vector<int>> Par(n+1,vector<int>(M,0));
    vector<int> dep(n+1,0);
    vector<int> tree(n+1,0);
    vector<vector<int>> max_vle(n+1,vector<int>(M,INT_MIN));
    readEdgeListIntoAdjacencyList(edges, gr);
    dfs_2D(1, 0, gr, Par, dep, tree, max_vle, a);
    
    vector<int> ret;
    for(int i=0;i<queries.size();i++){
        int u=queries[i][0];
        int v=queries[i][1];
        int lca=LCA_2D(u, v, dep, Par, max_vle, a);
        cout<<u<<" "<<v<<" "<<lca<<endl;
        ret.push_back(lca);
    }
    return ret;
}