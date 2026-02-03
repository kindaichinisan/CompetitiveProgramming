// 3825. Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND
// You are given an integer array nums.

// Return the length of the longest strictly increasing subsequence in nums whose bitwise AND is non-zero. If no such subsequence exists, return 0.

 

// Example 1:

// Input: nums = [5,4,7]

// Output: 2

// Explanation:

// One longest strictly increasing subsequence is [5, 7]. The bitwise AND is 5 AND 7 = 5, which is non-zero.

// Example 2:

// Input: nums = [2,3,6]

// Output: 3

// Explanation:

// The longest strictly increasing subsequence is [2, 3, 6]. The bitwise AND is 2 AND 3 AND 6 = 2, which is non-zero.

// Example 3:

// Input: nums = [0,1]

// Output: 1

// Explanation:

// One longest strictly increasing subsequence is [1]. The bitwise AND is 1, which is non-zero.

 

// Constraints:

// 1 <= nums.length <= 105
// 0 <= nums[i] <= 109​​​​​​​

// https://leetcode.com/problems/longest-strictly-increasing-subsequence-with-non-zero-bitwise-and/description/

int longestSubsequence(vector<int>& nums) {
        int n=nums.size();

        int maxi_len=0;
        for(int i=0;i<32;i++){
            int cur_bit=1<<i;

            vector<int> temp;
            for(int j=0;j<n;j++){
        
                if((nums[j]&cur_bit)!=0){
                    temp.push_back(nums[j]);
                }
            }

            vector<int> tails;
            for(int j=0;j<temp.size();j++){
                auto it = lower_bound(tails.begin(), tails.end(), temp[j]);
                if (it == tails.end())
                    tails.push_back(temp[j]);
                else
                    *it = temp[j];
            }

            if(maxi_len<tails.size())
                maxi_len=tails.size();
            
        }

        return maxi_len;
    }