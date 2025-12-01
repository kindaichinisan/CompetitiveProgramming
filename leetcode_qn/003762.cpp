// 3762. Minimum Operations to Equalize Subarrays

// You are given an integer array nums and an integer k.

// In one operation, you can increase or decrease any element of nums by exactly k.

// You are also given a 2D integer array queries, where each queries[i] = [li, ri].

// For each query, find the minimum number of operations required to make all elements in the subarray nums[li..ri] equal. If it is impossible, the answer for that query is -1.

// Return an array ans, where ans[i] is the answer for the ith query.

 

// Example 1:

// Input: nums = [1,4,7], k = 3, queries = [[0,1],[0,2]]

// Output: [1,2]

// Explanation:

// One optimal set of operations:

// i	[li, ri]	nums[li..ri]	Possibility	Operations	Final
// nums[li..ri]	ans[i]
// 0	[0, 1]	[1, 4]	Yes	nums[0] + k = 1 + 3 = 4 = nums[1]	[4, 4]	1
// 1	[0, 2]	[1, 4, 7]	Yes	nums[0] + k = 1 + 3 = 4 = nums[1]

// 			nums[2] - k = 7 - 3 = 4 = nums[1]	[4, 4, 4]	2
// Thus, ans = [1, 2].

// Example 2:

// Input: nums = [1,2,4], k = 2, queries = [[0,2],[0,0],[1,2]]

// Output: [-1,0,1]

// Explanation:

// One optimal set of operations:

// i	[li, ri]	nums[li..ri]	Possibility	Operations	Final
// nums[li..ri]	ans[i]
// 0	[0, 2]	[1, 2, 4]	No	-	[1, 2, 4]	-1
// 1	[0, 0]	[1]	Yes	Already equal	[1]	0
// 2	[1, 2]	[2, 4]	Yes	nums[1] + k = 2 + 2 = 4 = nums[2]	[4, 4]	1
// Thus, ans = [-1, 0, 1].

 

// Constraints:

// 1 <= n == nums.length <= 4 × 104
// 1 <= nums[i] <= 109​​​​​​​
// 1 <= k <= 109
// 1 <= queries.length <= 4 × 104
// ​​​​​​​queries[i] = [li, ri]
// 0 <= li <= ri <= n - 1

#define ll long long

class MergeSortTree {
private:
    vector<vector<int>> st;   // each node stores sorted values
    vector<vector<ll>> ps;   // each node stores prefix sum of sorted values
    int n;

    void build(int start, int ending, int node, const vector<int> &v) {
        if (start == ending) {
            st[node] = {v[start]};
            ps[node] = {(ll)v[start]};
            return;
        }

        int mid = (start + ending) / 2;
        build(start, mid, node*2+1, v);
        build(mid+1, ending, node*2+2, v);

        // merge two sorted children
        auto &L=st[node*2+1];
        auto &R=st[node*2+2];
        auto &V=st[node];
        V.resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), V.begin());

        auto &P=ps[node];
        P.resize(V.size());
        ll s=0LL;
        for(int i=0;i<V.size();i++){
            s+=V[i];
            P[i]=s;
        }
    }

    // count how many values ≤ x in [l, r]
    pair<int, ll> query(int start, int ending, int l, int r, int node, int x) {
        if (ending < l || start > r)
            return {0, 0LL};
        if (l <= start && ending <= r){
            int cntLE = upper_bound(st[node].begin(), st[node].end(), x) - st[node].begin();
            ll sumLE = cntLE>0 ? ps[node][cntLE-1] : 0LL;
            return {cntLE, sumLE};
        }
        int mid = (start+ending) / 2;
        auto left = query(start, mid, l, r, node*2+1, x);
        auto right = query(mid+1, ending, l, r, node*2+2, x);
        return {left.first + right.first, left.second+right.second};
    }

    ll querySum(int start, int ending, int l, int r, int node){
        if (ending < l || start > r)
            return 0LL;
        if (l <= start && ending <= r){
            return ps[node].back();
        }
        int mid = (start + ending) / 2;
        auto left = querySum(start, mid, l, r, node*2+1);
        auto right = querySum(mid+1, ending, l, r, node*2+2);
        return left + right;
    }

public:
    void init(int _n) {
        n = _n;
        st.assign(4*n, {});
        ps.assign(4*n, {});
    }

    void build(const vector<int> &v) {
        build(0, n-1, 0, v);
    }

    pair<int, ll> query(int l, int r, int x) {
        return query(0, n-1, l, r, 0, x);
    }

    ll querySum(int l, int r){
        return querySum(0, n-1, l, r, 0);
    }
};


class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n=nums.size();

        MergeSortTree t;
        t.init(n);
        t.build(nums);

        vector<int> l(n,0);
        vector<int> r(n,0);
        for(int i=0;i<n;i++){
            l[i]=i;
            if(i>=1){
                int diff=nums[i]-nums[i-1];
                if(diff%k==0){
                    l[i]=l[i-1];
                }
            }
        }
        
        for(int i=n-1;i>=0;i--){
            r[i]=i;
            if(i<n-1){
                int diff=nums[i+1]-nums[i];
                if(diff%k==0){
                    r[i]=r[i+1];
                }
            }
        }

        //binary search on uniq so that no duplicate in binary search.
        vector<int> uniq=nums;
        sort(uniq.begin(), uniq.end());
        uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

        int q=queries.size();

        vector<ll> ret_list;
        for(int i=0;i<q;i++){
            int l_=queries[i][0];
            int r_=queries[i][1];

            if(l[l_]==l[r_] && r[l_]==r[r_]){

                int len=r_-l_+1;
                int need=(len+1)/2;
                int low=0;
                int high=uniq.size()-1;
                int best=high;
                while(low<=high){
                    int mid=(low+high)/2;
                    auto LE=t.query(l_, r_, uniq[mid]);
                    int cntLE=LE.first;
                    if(cntLE>=need){ //uniq[mid] is too big, find smaller one
                        best=mid;
                        high=mid-1;
                    }
                    else{ //uniq[mid] is too small, find bigger one
                        low=mid+1;
                    }
                }

                //best is the idx of median
                int median=uniq[best];
                auto LE=t.query(l_, r_, median);
                int cntLE=LE.first;
                ll sumLE=LE.second;
                int cntG=len-cntLE;
                ll sum=t.querySum(l_, r_);
                ll sumG=sum-sumLE;
                ll ret=sumG-(ll)median*cntG+(ll)median*cntLE-sumLE;
                ret/=k;
                
                ret_list.push_back(ret);
            }
            else{
                ret_list.push_back(-1LL);
            }
                
        }

        return ret_list;
    }
};