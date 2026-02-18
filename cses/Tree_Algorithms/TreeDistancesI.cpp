// CSES Problem Set
// Tree Distances I
// You are given a tree consisting of n nodes.
// Your task is to determine for each node the maximum distance to another node.
// Input
// The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n.
// Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
// Output
// Print n integers: for each node 1,2,\ldots,n, the maximum distance to another node.
// Constraints

// 1 \le n \le 2 \cdot 10^5
// 1 \le a,b \le n

// Example
// Input:
// 5
// 1 2
// 1 3
// 3 4
// 3 5

// Output:
// 2 3 2 3 3
// https://cses.fi/problemset/task/1132/


#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+1;
const int M = 20;

void readEdgeList(int n, vector<vector<int>>& edges){
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        edges.push_back({u, v});
    }
}

void printEdgeList(vector<vector<int>> edges){
    for(int i=0;i<(int)edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        cout<<u<<" "<<v<<endl;
    }
}

void printTree(int n, int tree[N]){
    for(int i=1;i<=n;i++){
        cout<<"tree["<<i<<"]: "<<tree[i]<<endl;
    }
}

void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<int> gr[N]){
    for(int i=0;i<(int)edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

//parent sparse table (2D parent)
int dfs_2D(int cur, int par, vector<int> gr[N], int Par[N][M], int dep[N], int tree[N]) {
    // cout<<"at node "<<cur<<endl;
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

    // cout<<"node["<<cur<<"]: "<<tree[cur]<<endl;

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

//this will TLE if many leaf nodes. potentially n^2
vector<int> solve(int n, vector<vector<int>> edges)
{
    
    vector<int> gr[N];
    // printEdgeList(edges);
    readEdgeListIntoAdjacencyList(edges, gr);
    int Par[N][M];
    int tree[N];
    int dep[N];
    memset(tree, 0, sizeof(int)*N);
    dep[0]=0;
    dfs_2D(1,0,gr,Par,dep,tree);
    //printParent_2D(n, Par);
    // printTree(n, tree);
    
    vector<int> leafnode_list;
    for(int i=1;i<=n;i++){
        if(tree[i]==1){
            leafnode_list.push_back(i);
        }
    }
    
    vector<int> ret;
    for(int i=1;i<=n;i++){
        int max_dist=dep[i]-dep[1]; //consider distance to root.
        for(int j=0;j<(int)leafnode_list.size();j++){
            int leafnode=leafnode_list[j];
            int lca=LCA(i,leafnode,dep,Par);
            int dist=dep[i]+dep[leafnode]-2*dep[lca];
            // cout<<"leafnode "<<i<<" "<<leafnode<<" "<<lca<<" "<<dist<<endl;
            max_dist=max(max_dist,dist);
        }
        ret.push_back(max_dist);
    }
    return ret;
}

//reduce it to O(n)
vector<int> solve2(int n, vector<vector<int>> edges)
{
    
    vector<int> gr[N];
    // printEdgeList(edges);
    readEdgeListIntoAdjacencyList(edges, gr);
    int Par[N][M];
    int tree[N];
    int dep[N];
    int depB[N];

    //DFS from root
    memset(tree, 0, sizeof(int)*N);
    dep[0]=0;
    dfs_2D(1,0,gr,Par,dep,tree);
    int max_depth=0;
    int nodeA;//1 extreme node from root
    for(int i=1;i<=n;i++){
        if(max_depth<dep[i]){
            max_depth=dep[i];
            nodeA=i;
        }
    }

    //DFS from nodeA
    memset(tree, 0, sizeof(int)*N);
    dep[0]=0;
    dfs_2D(nodeA,0,gr,Par,dep,tree);
    max_depth=0;
    int nodeB;//another extreme node from nodeA
    for(int i=1;i<=n;i++){
        if(max_depth<dep[i]){
            max_depth=dep[i];
            nodeB=i;
        }
    }

    //DFS from nodeB
    memset(tree, 0, sizeof(int)*N);
    depB[0]=0;
    dfs_2D(nodeB,0,gr,Par,depB,tree);
    // cout<<"nodeAB "<<nodeA<<" "<<nodeB<<endl;


    vector<int> ret;
    for(int i=1;i<=n;i++){
        int max_dist=max(dep[i], depB[i]);
        // cout<<"dep"<<dep[i]<<" "<<depB[i]<<endl;

        ret.push_back(max_dist-1);
    }
    return ret;
}

int main(){
    int n; //number of nodes
    vector<vector<int>> edges; //edge list

    cin>>n;
    readEdgeList(n, edges);

    vector<int> ret = solve2(n, edges);

    for(int i=0;i<ret.size();i++){
        cout<<ret[i]<<" ";
    }
    cout<<endl;
}