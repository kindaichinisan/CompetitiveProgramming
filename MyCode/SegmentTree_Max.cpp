#include<bits/stdc++.h>

using namespace std;

//max
class SegmentTree_Max{

    private:
    vector<int> st;
    int n;

    const int default_vle=INT_MIN;
    const int ROOT=0;
    
    //recursion
    void build(int node, int start, int ending, vector<int> &v){
        // leaf node base case
        if(start==ending){
            st[node]=v[start];
            
            return;
        }
        int mid=(start+ending)/2;

        //left subtree is (start, mid)
        build(2*node+1, start, mid, v);

        //right subtree is (mid+1, ending)
        build(2*node+2, mid+1, ending, v);
        
        //build the cur node
        st[node]=max(st[node*2+1],st[node*2+2]);
    }

    int query(int node, int start, int ending, int l, int r){
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
        int q1=query(2*node+1, start, mid, l, r);
        int q2=query(2*node+2, mid+1, ending, l, r);

        return max(q1,q2);
    }

    void update(int node, int start, int ending, int index, int value){
        //base case
        if(start==ending){
            st[node]=value;
            return;
        }

        int mid=(start+ending)/2;
        if(index<=mid){
            //left subtree
            update(2*node+1, tart, mid, index, value);
        }
        else{
            //right subtree
            update(2*node+2, mid+1, ending, index, value);

        }

        st[node] = max(st[node * 2 + 1], st[node * 2 + 2]);
    }

    public:
    void init(int _n){
        this->n=_n;
        st.resize(4*n, default_vle);
    }

    void build(vector<int> &v){
        build(ROOT, 0, n-1, v);
    }

    int query(int l, int r){
        return query(ROOT, 0, n-1, l, r);
    }
    void update(int index, int value){
        update(ROOT, 0, n-1, index, value);
    }

    int getDefault(){
        return default_vle;
    }

};

//usage
// vector<int> v={1,2, 3, 4, 5, 6, 7, 8};
// SegmentTree tree;
// tree.init(v.size());
// tree.build(v);
// tree.query(0, 4);
// tree.update(4, 10);