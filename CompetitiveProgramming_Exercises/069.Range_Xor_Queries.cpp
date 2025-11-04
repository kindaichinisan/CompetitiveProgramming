// Range Xor Queries
// You are given an array a of n integers, and an array queries where queries[i] = [ a, b ] for each query, you have to find the xor sum of the values in the range [ a, b ].

// Return an array containing answer for each query respectively.

// Constraints:

// 1<= n, queries.length <= 10^5

// 1<= xi <= 10^9

// 1<=  a , b <= n

// Example:

// Input

// n = 5 , a =[3, 2, 4, 5, 1, 1, 5, 3]
// queries = [
//     [2, 4],
//     [5, 6],
//     [1, 8],
//     [3, 3]
// ]
// Output

// [3, 0, 6, 4]

#include<bits/stdc++.h>
using namespace std;

//xor
//xor
class SegmentTree_Xor{

    private:
    vector<int> st;
    int n;
    
    //recursion
    void build(int start, int ending, int node, vector<int> &v){
        // leaf node base case
        if(start==ending){
            st[node]=v[start];
            return;
        }
        int mid=(start+ending)/2;

        //left subtree is (start, mid)
        build(start, mid, 2*node+1, v);

        //right subtree is (mid+1, ending)
        build(mid+1, ending, 2*node+2, v);
        
        //build the cur node
        st[node]=st[node*2+1] ^ st[node*2+2];
    }

    int query(int start, int ending, int l, int r, int node){
        //current subtree does not overlap with query range
        if(start>r || ending<l){
            return 0;
        }

        //current subtree is totally inside query range
        if(start>=l && ending<=r){
            return st[node];
        }

        //current subtree is partially inside query range
        int mid=(start+ending)/2;
        int q1=query(start, mid, l, r, 2*node+1);
        int q2=query(mid+1, ending, l, r, 2*node+2);

        return q1 ^ q2;
    }

    void update(int start, int ending, int node, int index, int value){
        //base case
        if(start==ending){
            st[node]=value;
            return;
        }

        int mid=(start+ending)/2;
        if(index<=mid){
            //left subtree
            update(start, mid, 2*node+1, index, value);
        }
        else{
            //right subtree
            update(mid+1, ending, 2*node+2, index, value);
        }

        st[node] = st[node * 2 + 1] ^ st[node * 2 + 2];
    }

    public:
    void init(int _n){
        this->n=_n;
        st.resize(4*n, 0);
    }

    void build(vector<int> &v){
        build(0, n-1, 0, v);
    }

    int query(int l, int r){
        return query(0, n-1, l, r, 0);
    }

    void update(int index, int value){
        update(0, n-1, 0, index, value);
    }

};

vector<int>solve(int n, vector<int>a, vector<vector<int>> queries){
    SegmentTree_Xor tree;
    tree.init(n);
    tree.build(a);
    
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
    vector<int> ret;
    
    int q=queries.size();
    
    for(int i=0;i<q;i++){
        int l=queries[i][0]-1;
        int r=queries[i][1]-1;
        cout<<l<<" "<<r<<endl;
        int ans=tree.query(l, r);
        ret.push_back(ans);
    }
    
    return ret;
}