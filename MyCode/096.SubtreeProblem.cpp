// Subtree Problem
// You are given a tree with n nodes rooted at 1  where each node is numbered 1 to n.

// The tree is given as an array of edges where edges[i] = [ui, vi] is a bidirectional edge between node ui and node vi , and also you are given an array of queries where query[i] = ui , you have to count the number of nodes present in the subtree of  node ui for each query.

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
 
// queries = [ 1, 2, 3, 4, 5]
// Output

// [5, 1, 3, 1, 1]


#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+1;

int dfs(int cur, int par, vector<int> gr[N], int Par[N], int tree[N]) {
	Par[cur] = par;
	tree[cur]++;
	for (auto x : gr[cur]) {
		if (x != par) {
			// x is child node
			tree[cur]+=dfs(x, cur, gr, Par, tree);
		}
	}
	
	return tree[cur];
}

void readEdgeListIntoAdjacencyList(vector<vector<int>> edges, vector<int> gr[N]){
    for(int i=0;i<edges.size();i++){
        int u=edges[i][0];
        int v=edges[i][1];
        
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

vector<int> subtreeProblem (int n, vector<vector<int>> edges, vector<int> queries)
{
    vector<int> gr[N];
    int Par[N];
    int tree[N];
        
    readEdgeListIntoAdjacencyList(edges, gr);
    
    // memset(tree, 0, N*sizeof(int));
    dfs(1, 0, gr, Par, tree);
    
    vector<int> ret;
    for(int i=0;i<queries.size();i++){
        ret.push_back(tree[queries[i]]);
    }
    return ret;
}