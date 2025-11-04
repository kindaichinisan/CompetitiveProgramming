// Range Minimum Queries
// Given an array arr of n integers, your task is to process queries of the following types:

// update the value at position k to u

// what is the minimum value in range [a,b]?

// return an array containing answers for type 2 queries respectively.

// Constraints:

// 1<= n, queries.length <= 10^5

// 1<= a<=b  <=n

// 1<= u <= n

// 1<= arri , u <= 10^9

// Example:

// Input

// n = 8 , arr =[3, 2, 4, 5, 1, 1, 5, 3]
// queries = [
//     [2, 1, 4],
//     [2, 5, 6],
//     [1, 2, 3],
//     [2, 1, 4]
// ]
// Output

// [2, 1, 3]

#include<bits/stdc++.h>
using namespace std;

class SegmentTree_Min{

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
        st[node]=min(st[node*2+1],st[node*2+2]);
    }

    int query(int start, int ending, int l, int r, int node){
        //current subtree does not overlap with query range
        if(start>r || ending<l){
            return INT_MAX;
        }

        //current subtree is totally inside query range
        if(start>=l && ending<=r){
            return st[node];
        }

        //current subtree is partially inside query range
        int mid=(start+ending)/2;
        int q1=query(start, mid, l, r, 2*node+1);
        int q2=query(mid+1, ending, l, r, 2*node+2);

        return min(q1,q2);
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

        st[node] = min(st[node * 2 + 1], st[node * 2 + 2]);
    }

    public:
    void init(int _n){
        this->n=_n;
        st.resize(4*n, INT_MAX);
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

vector<int> solve(int n, vector<int>arr, vector<vector<int>> queries){
    SegmentTree_Min tree;
    tree.init(n);
    tree.build(arr);
    
    int q=queries.size();
    vector<int> ret;
    for(int i=0;i<q;i++){
        cout<<queries[i][0]<<" "<<queries[i][1]<<" "<<queries[i][2]<<endl;
        int type=queries[i][0];
        
        if(type==1){
            int idx=queries[i][1]-1;
            int vle=queries[i][2];
            tree.update(idx, vle);
        }
        else{
            int l=queries[i][1]-1;
            int r=queries[i][2]-1;
            int ans=tree.query(l,r);
            ret.push_back(ans);
        }
        
    }
    return ret;
}