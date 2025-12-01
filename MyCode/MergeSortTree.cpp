#include<bits/stdc++.h>

using namespace std;

// difference between MergeSortTree and SegmentTree
// node contains sorted vector instead of single vle 
// build step uses merge()
// query step return binary search results
// no update as it is hard O((log (N))^2. Use other tree (Fenwick of ordered set or PBDS tree) if update is needed.
class MergeSortTree {
private:
    vector<vector<int>> st;   // each node stores sorted values
    int n;
    const int ROOT=0;

    void build(int node, int start, int ending, const vector<int> &v) {
        if (start == ending) {
            st[node] = {v[start]};
            return;
        }

        int mid = (start + ending) / 2;
        build(node*2+1, start, mid, v);
        build(node*2+2, mid+1, ending, v);

        // merge two sorted children
        st[node].resize(st[node*2+1].size() + st[node*2+2].size());
        merge(st[node*2+1].begin(), st[node*2+1].end(),
              st[node*2+2].begin(), st[node*2+2].end(),
              st[node].begin()); //merge sort using std::merge
    }

    // count how many values ≤ x in [l, r]
    int query(int node, int start, int ending, int l, int r, int x) {
        if (ending < l || start > r) //no overlap
            return 0;
        //current subtree is totally inside query range
        if(start>=l && ending<=r){
            return upper_bound(st[node].begin(), st[node].end(), x) 
                   - st[node].begin();
        }

        //current subtree is partially inside query range
        int mid = (start + ending) / 2;
        return query(node*2+1, start, mid, l, r, x) +
               query(node*2+2, mid+1, ending, l, r, x);
    }

public:
    void init(int _n) {
        n = _n;
        st.assign(4*n, {});
    }

    void build(const vector<int> &v) {
        build(ROOT, 0, n-1, v);
    }

    int query(int l, int r, int x) {
        return query(ROOT, 0, n-1, l, r, x);
    }
};
