#include<bits/stdc++.h>

using namespace std;

class TreeAlgorithm_Heap{

    const int M = 20;

    void readEdgeList(int n, vector<vector<int>>& edges){
        for(int i=0;i<n-1;i++){
            int u,v;
            cin>>u>>v;
            edges.push_back({u, v});
        }
    }

    void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<vector<int>>& gr){
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
    }

    void printEdgeList(const vector<vector<int>>& edges){
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            
            cout<<u<<" "<<v<<endl;
        }
    }

    void printParent_1D(int n, const vector<int>& Par){
        for(int i=1;i<=n;i++){
            cout<<"Par["<<i<<"]: "<<Par[i]<<endl;
        }
    }

    void printParent_2D(int n, const vector<vector<int>>& Par){
        for(int i=1;i<=n;i++){

            cout<<i<<" ";

            for(int j=0;j<M;j++){
                cout<<Par[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void printTree(int n, const vector<int>& tree){
        for(int i=1;i<=n;i++){
            cout<<"tree["<<i<<"]: "<<tree[i]<<endl;
        }
    }

    //graph node shld start from 1 onward. root node parent is 0. dfs(1, 0, gr, Par, tree)
    //if graph node start from 0 onward, root node parent is -1
    //store the parent of node and number of nodes in subtree of node
    //assumption: dep[0]=0, tree[0:N]=0
    //Par is 1D array (non-binary lifting)
    //immediate parent (1D parent)
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
        
    //parent sparse table (2D parent)
    int dfs_2D(int cur, int par, const vector<vector<int>>& gr, vector<vector<int>>& Par, vector<int>& dep, vector<int>& tree) {
        dep[cur] = dep[par] + 1;

        Par[cur][0] = par;
        tree[cur]=1;
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
};

//how to use 2D
// vector<vector<int>> gr(n+1, vector<int>());
// vector<vector<int>> Par(n+1,vector<int>(M,0));
// vector<int> dep(n+1,0);
// vector<int> tree(n+1,0);
// readEdgeListIntoAdjacencyList(edges, gr);
// dfs_2D(1, 0, gr, Par, dep, tree);

//how to use 1D
// vector<vector<int>> gr(n+1, vector<int>());
// vector<int> Par(n+1,0);
// vector<int> dep(n+1,0);
// vector<int> tree(n+1,0);
// readEdgeListIntoAdjacencyList(edges, gr);
// dfs_1D(1, 0, gr, Par, dep, tree);