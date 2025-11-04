#include<bits/stdc++.h>

using namespace std;

//min
class SegmentTree_Min{

    private:
    vector<int> st;
    int n;

    const int default_vle=INT_MAX;
    
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
            return default_vle;
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
        st.resize(4*n, default_vle);
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

//usage
// vector<int> v={1,2, 3, 4, 5, 6, 7, 8};
// SegmentTree tree;
// tree.init(v.size());
// tree.build(v);
// tree.query(0, 4);
// tree.update(4, 10);