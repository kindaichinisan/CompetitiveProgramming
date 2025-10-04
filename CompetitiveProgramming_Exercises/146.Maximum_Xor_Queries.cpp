// Maximum Xor Queries
// You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].

// The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.

// Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.

// Constraints:

// 1 <= nums.length, queries.length <= 10^5

// queries[i].length == 2

// 0 <= nums[j], xi, mi <= 10^9

// Example:

// Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
// Output: [3,3,7]
 
// Explanation:
// 1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
// 2) 1 XOR 2 = 3.
// 3) 5 XOR 2 = 7.

#include<bits/stdc++.h>
using namespace std;

class binary_trie{

public:
    struct node {
        node *nxt[2];
        bool is_end;
        int level;
        
        node(int _level) {
            for (int i = 0; i < 2; i++) nxt[i] = NULL;
            is_end = false;
            level=_level;
        }
    };

    node *root;
    
    binary_trie(){
        root=new node(0);
    }

    void insert(int num) {
        node *cur = root;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (cur->nxt[bit] == NULL){
                cur->nxt[bit] = new node(cur->level+1);
            }
            cur = cur->nxt[bit];
        }
        // cur -> last node
        cur->is_end = true;
    }

    //to use with xor question when opposite bit is preferred.
    int query(int x) {
        node *cur = root;
        if (!cur->nxt[0] && !cur->nxt[1]) return -1; // empty trie
        int res = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int prefer = 1 - bit; // opposite bit preferred
            if (cur->nxt[prefer]) {
                res |= (1 << i);
                cur = cur->nxt[prefer];
            } else {
                cur = cur->nxt[bit];
            }
        }
        return res;
    }
};

vector<int> maximizeXor(vector<int> nums, vector<vector<int>> queries) {
    binary_trie t;
    
    sort(nums.begin(),nums.end());
    
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<endl;
    }
    
    for(int i=0;i<queries.size();i++){
        cout<<queries[i][0]<<" "<<queries[i][1]<<endl;
    }
    
    vector<array<int,3>> q;
    
    for(int i=0;i<queries.size();i++){
        q.push_back({queries[i][1],queries[i][0],i});
    }
    
    sort(q.begin(),q.end());
    
    vector<int> ans(q.size(),-1);
    int num_idx=0;
    for(int i=0;i<q.size();i++){
        int x=q[i][1];
        int m=q[i][0];
        int idx=q[i][2];
        
        while(num_idx<nums.size() && nums[num_idx]<=m){
            t.insert(nums[num_idx++]);
        }
        
        if(num_idx>0){
            ans[idx]=t.query(x);
        }
    }
    
    return ans;
}