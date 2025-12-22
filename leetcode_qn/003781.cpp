// 3781. Maximum Score After Binary Swaps

// You are given an integer array nums of length n and a binary string s of the same length.

// Initially, your score is 0. Each index i where s[i] = '1' contributes nums[i] to the score.

// You may perform any number of operations (including zero). In one operation, you may choose an index i such that 0 <= i < n - 1, where s[i] = '0', and s[i + 1] = '1', and swap these two characters.

// Return an integer denoting the maximum possible score you can achieve.

 

// Example 1:

// Input: nums = [2,1,5,2,3], s = "01010"

// Output: 7

// Explanation:

// We can perform the following swaps:

// Swap at index i = 0: "01010" changes to "10010"
// Swap at index i = 2: "10010" changes to "10100"
// Positions 0 and 2 contain '1', contributing nums[0] + nums[2] = 2 + 5 = 7. This is maximum score achievable.

// Example 2:

// Input: nums = [4,7,2,9], s = "0000"

// Output: 0

// Explanation:

// There are no '1' characters in s, so no swaps can be performed. The score remains 0.

 

// Constraints:

// n == nums.length == s.length
// 1 <= n <= 105
// 1 <= nums[i] <= 109
// s[i] is either '0' or '1'

// https://leetcode.com/problems/maximum-score-after-binary-swaps/description/

class Solution {
public:

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
    //1 can only move left
    //find the number of 1 and the rightmost 1
    long long maximumScore(vector<int>& nums, string s) {
        int n=nums.size();

        SegmentTree_Max_With_Idx tree;
        tree.init(nums.size());
        tree.build(nums);

        long long sum=0LL;
        

        for(int i=0;i<=n;i++){
            if(s[i]=='1'){
                pair<int, int> maxi=tree.query(0, i);
                sum+=maxi.first;
                tree.update(maxi.second, tree.getDefault().first);
            }
        }
        return sum;
    }
};