// 3878. Count Good Subarrays

// You are given an integer array nums.

// A subarray is called good if the bitwise OR of all its elements is equal to at least one element present in that subarray.

// Return the number of good subarrays in nums.

// Here, the bitwise OR of two integers a and b is denoted by a | b.

 

// Example 1:

// Input: nums = [4,2,3]

// Output: 4

// Explanation:

// The subarrays of nums are:

// Subarray	Bitwise OR	Present in Subarray
// [4]	4 = 4	Yes
// [2]	2 = 2	Yes
// [3]	3 = 3	Yes
// [4, 2]	4 | 2 = 6	No
// [2, 3]	2 | 3 = 3	Yes
// [4, 2, 3]	4 | 2 | 3 = 7	No
// Thus, the good subarrays of nums are [4], [2], [3] and [2, 3]. Thus, the answer is 4.

// Example 2:

// Input: nums = [1,3,1]

// Output: 6

// Explanation:

// Any subarray of nums containing 3 has bitwise OR equal to 3, and subarrays containing only 1 have bitwise OR equal to 1.

// In both cases, the result is present in the subarray, so all subarrays are good, and the answer is 6.

 

// Constraints:

// 1 <= nums.length <= 105
// 0 <= nums[i] <= 109

// https://leetcode.com/problems/count-good-subarrays/description/

// initially this algo got TLE.
// Due to using vector<vector<int>> which has different storage mechanism than vector<Node> or vector<array<int,3>>
// vector<vector<int>> is stored as [vec][vec][vec]...
// Each vec has its own heap allocation (store pointer + size + capacity). Has pointer chasing, scattered memory and many allocation.
// vector<Node> is stored as [Node][Node][Node]...
// Each Node is [int][int][int]. Everything is packed tightly in one block.
// Heap allocations is very expensive.
// vector<Node> has 1 allocation total whereas vector<vector<int>> has 1 allocation for outer vector, 1 allocation per inner vector.
// CPU loves contiguous memory for cache hit during sequential access. vector<Node> will have many cache hit whereas vector<vector<int>> will have many cache miss as each inner vector is somewhere else in memory.
// object size overhead: vector<int> has aditional overhead like pointer (8Bytes), size (8Bytes), capacity (8Bytes).
// Node will use 12B, wheras vector<int> will use ~24B + heap allocation.
// using Node or array<int,3>: Node has semantic meaning, array<int,3> may be optimized more aggressively by compiler.
// reserve helps to allocate memory once, if not, vector capacity will grow 0 -> 1 -> 2 -> 4 -> 8 -> 16 -> 32

class Solution {
public:
    long long countGoodSubarrays(vector<int>& nums) {
        int n=nums.size();

        vector<vector<int>> prev;
        long long ans=0;
        for(int i=0;i<n;i++){
            int num=nums[i];

            vector<vector<int>> cur;
            cur.push_back({num,1,num});
            ans+=1;
            for(int j=0;j<prev.size();j++){
                int or_vle=num | prev[j][0];
                int cnt=prev[j][1];
                int max_vle=max(num,prev[j][2]);

                if(max_vle==or_vle){
                    ans+=cnt;
                }
                if(cur.back()[0]==or_vle){
                    cur.back()[1]+=cnt;
                    cur.back()[2]=max_vle;
                }
                else{
                    cur.push_back({or_vle,cnt,max_vle});
                }
            }

            prev=move(cur);

        }

        return ans;
    }
};