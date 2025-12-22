#include<bits/stdc++.h>

using namespace std;

//max
class SegmentTree_Max_With_Idx{

    private:
    vector<pair<int, int>> st;
    int n;

    const pair<int, int> default_vle={INT_MIN, -1};
    const int ROOT=0;
    
    //recursion
    void build(int node, int start, int ending, vector<int> &v){
        // leaf node base case
        if(start==ending){
            st[node]={v[start],start};
            
            return;
        }
        int mid=(start+ending)/2;

        //left subtree is (start, mid)
        build(2*node+1, start, mid, v);

        //right subtree is (mid+1, ending)
        build(2*node+2, mid+1, ending, v);
        
        //build the cur node
        if(st[node*2+1].first>=st[node*2+2].first)
            st[node]=st[node*2+1];
        else
            st[node]=st[node*2+2];
    }

    pair<int, int> query(int node, int start, int ending, int l, int r){
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
        pair<int, int> q1=query(2*node+1, start, mid, l, r);
        pair<int, int> q2=query(2*node+2, mid+1, ending, l, r);

        if(q1.first>=q2.first)
            return q1;
        else
            return q2;
    }

    void update(int node, int start, int ending, int index, int value){
        //base case
        if(start==ending){
            st[node].first=value;
            return;
        }

        int mid=(start+ending)/2;
        if(index<=mid){
            //left subtree
            update(2*node+1, start, mid, index, value);
        }
        else{
            //right subtree
            update(2*node+2, mid+1, ending, index, value);

        }

        if(st[node*2+1].first>=st[node*2+2].first)
            st[node]=st[node*2+1];
        else
            st[node]=st[node*2+2];
    }

    public:
    void init(int _n){
        this->n=_n;
        st.resize(4*n, default_vle);
    }

    void build(vector<int> &v){
        build(ROOT, 0, n-1, v);
    }

    pair<int, int> query(int l, int r){
        return query(ROOT, 0, n-1, l, r);
    }
    void update(int index, int value){
        update(ROOT, 0, n-1, index, value);
    }

    pair<int, int> getDefault(){
        return default_vle;
    }

};

//usage
// vector<int> v={1, 2, 3, 4, 5, 6, 7, 8};
// SegmentTree tree;
// tree.init(v.size());
// tree.build(v);
// tree.query(0, 4); => returns {5, 4}
// tree.update(4, 10); => leaf_node={{1,0}, {2,1}, {3,2}, {4,3}, {10,4}, {6,5}, {7,6}, {8,7}};
// start, ending, index is v index
// node is tree idx