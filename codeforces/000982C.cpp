// C. Cut 'em all!
// time limit per test1 second
// memory limit per test256 megabytes
// You're given a tree with n vertices.

// Your task is to determine the maximum possible number of edges that can be removed in such a way that all the remaining connected components will have even size.

// Input
// The first line contains an integer n (1≤n≤105) denoting the size of the tree.

// The next n−1 lines contain two integers u, v (1≤u,v≤n) each, describing the vertices connected by the i-th edge.

// It's guaranteed that the given edges form a tree.

// Output
// Output a single integer k — the maximum number of edges that can be removed to leave all connected components with even size, or −1 if it is impossible to remove edges in order to satisfy this property.

// Examples
// InputCopy
// 4
// 2 4
// 4 1
// 3 1
// OutputCopy
// 1
// InputCopy
// 3
// 1 2
// 1 3
// OutputCopy
// -1
// InputCopy
// 10
// 7 1
// 8 4
// 8 10
// 4 7
// 6 5
// 9 3
// 3 5
// 2 10
// 2 5
// OutputCopy
// 4
// InputCopy
// 2
// 1 2
// OutputCopy
// 0
// Note
// In the first example you can remove the edge between vertices 1 and 4. The graph after that will have two connected components with two vertices in each.

// In the second example you can't remove edges in such a way that all components have even number of vertices, so the answer is −1.

// https://codeforces.com/problemset/problem/982/C

#include<bits/stdc++.h>

using namespace std;

const int N = 1e5+1;

void readEdgeList(int n, vector<vector<int>>& edges){
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        edges.push_back({u, v});
    }
}


void printEdgeList(vector<vector<int>> edges){
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        cout<<u<<" "<<v<<endl;
    }
}

void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<int> gr[N]){
    //cout<<"edgelist"<<endl;
    //printEdgeList(edges);
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

void printParent(int n, int Par[N]){
    for(int i=1;i<=n;i++){
        cout<<"Par["<<i<<"]: "<<Par[i]<<endl;
    }
}

void printTree(int n, int tree[N]){
    for(int i=1;i<=n;i++){
        cout<<"tree["<<i<<"]: "<<tree[i]<<endl;
    }
}

int dfs(int cur, int par, vector<int> gr[N], int Par[N], int tree[N]) {
    Par[cur] = par;
    
    tree[cur]++;
    for (auto x : gr[cur]) {
        if (x != par) {
            // x is child node
            tree[cur]+=dfs(x, cur, gr, Par, tree);
        }
    }
    //cout<<cur<<" "<<tree[cur]<<endl;
    
    return tree[cur];
}

int solve(int n, vector<vector<int>> edges)
{
    
    //printEdgeList(edges);
    if(n%2==1){
        return -1;
    }
    
    vector<int> gr[N];
    int Par[N];
    int tree[N];
    memset(tree, 0, sizeof(int)*N); //must memset else it will be random number
    readEdgeListIntoAdjacencyList(edges, gr);
    dfs(1, 0, gr, Par, tree);
    //printParent(n, Par);
    //printTree(n, tree);

    int cnt=0;
    for(int i=1;i<=n;i++){
        //cout<<i<<" "<<tree[i]<<endl;
        if(tree[i]>0 && tree[i]%2==0){
            cnt++;
        }
    }
    //number of edges is n-1
    //to divide the tree into forest with trees with 2 nodes each
    return cnt-1;
}

int main(){
    int n; //number of nodes
    vector<vector<int>> edges; //edge list

    cin>>n;
    readEdgeList(n, edges);

    int ret = solve(n, edges);

    cout<<ret<<endl;
}