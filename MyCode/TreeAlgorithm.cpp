#include<bits/stdc++.h>

using namespace std;

class TreeAlgorithm{

    const int N = 1e5+1;

    void readEdgeList(int n, vector<vector<int>>& edges){
        for(int i=0;i<n-1;i++){
            int u,v;
            cin>>u>>v;
            edges.push_back({u, v});
        }
    }

    void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<int> gr[N]){
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
    }

    void printEdgeList(vector<vector<int>> edges){
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            
            cout<<u<<" "<<v<<endl;
        }
    }

    void printParent_1D(int n, int Par[N]){
        for(int i=1;i<=n;i++){
            cout<<"Par["<<i<<"]: "<<Par[i]<<endl;
        }
    }

    void printParent_2D(int n, int Par[N][M]){
        for(int i=1;i<=n;i++){

            cout<<i<<" ";

            for(int j=0;j<M;j++){
                cout<<Par[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void printTree(int n, int tree[N]){
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
    int dfs_1D(int cur, int par, vector<int> gr[N], int Par[N], int dep[N], int tree[N]) {
        dep[cur] = dep[par] + 1;
        Par[cur] = par;
        tree[cur]++;
        for (auto x : gr[cur]) {
            if (x != par) {
                // x is child node
                tree[cur]+=dfs_1D(x, cur, gr, Par, dep, tree);
            }
        }
        
        return tree[cur];
    }
        
    //parent sparse table (2D parent)
    int dfs_2D(int cur, int par, vector<int> gr[N], int Par[N][M], int dep[N], int tree[N]) {
        dep[cur] = dep[par] + 1;

        Par[cur][0] = par;
        tree[cur]++;
        for (int j = 1; j < M; j++) {
            Par[cur][j] = Par[Par[cur][j - 1]][j - 1];
        }

        for (auto x : gr[cur]) {
            if (x != par) {
                tree[cur]+=dfs(x, cur, gr, Par, dep, tree);
            }
        }

        return tree[cur];
    }

    int LCA(int u, int v, int dep[N], int Par[N][M]) {
        
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

//int Par[N] will be modified as it is array (pass by reference)
//vector<int> a will not be modified as it is vector. (pass by value)
//how to use
// const int N = 1e5+1;
// const int M = 20;
// int n; //number of nodes
// vector<vector<int>> edges; //edge list
// vector<int> gr[N];
// int Par[N]; or
// int Par[N][M];
// int tree[N];
// int dep[N];
// memset(tree, 0, sizeof(int)*N);
// dep[0]=0;
// readEdgeListIntoAdjacencyList(edges, gr);
// dfs(1, 0, gr, Par, tree);