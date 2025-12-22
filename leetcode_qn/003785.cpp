// 3785. Minimum Swaps to Avoid Forbidden Values

// You are given two integer arrays, nums and forbidden, each of length n.

// You may perform the following operation any number of times (including zero):

// Choose two distinct indices i and j, and swap nums[i] with nums[j].
// Return the minimum number of swaps required such that, for every index i, the value of nums[i] is not equal to forbidden[i]. If no amount of swaps can ensure that every index avoids its forbidden value, return -1.

 

// Example 1:

// Input: nums = [1,2,3], forbidden = [3,2,1]

// Output: 1

// Explanation:

// One optimal set of swaps:

// Select indices i = 0 and j = 1 in nums and swap them, resulting in nums = [2, 1, 3].
// After this swap, for every index i, nums[i] is not equal to forbidden[i].
// Example 2:

// Input: nums = [4,6,6,5], forbidden = [4,6,5,5]

// Output: 2

// Explanation:

// One optimal set of swaps:
// Select indices i = 0 and j = 2 in nums and swap them, resulting in nums = [6, 6, 4, 5].
// Select indices i = 1 and j = 3 in nums and swap them, resulting in nums = [6, 5, 4, 6].
// After these swaps, for every index i, nums[i] is not equal to forbidden[i].
// Example 3:

// Input: nums = [7,7], forbidden = [8,7]

// Output: -1

// Explanation:

// It is not possible to make nums[i] different from forbidden[i] for all indices.
// Example 4:

// Input: nums = [1,2], forbidden = [2,1]

// Output: 0

// Explanation:

// No swaps are required because nums[i] is already different from forbidden[i] for all indices, so the answer is 0.

// https://leetcode.com/problems/minimum-swaps-to-avoid-forbidden-values/description/
// read https://leetcode.com/problems/minimum-swaps-to-avoid-forbidden-values/solutions/7427529/simple-solution-detailed-explanation-beg-pusi/
class Solution {
public:
    //3 observations:
    //1. number of vles in nums and forbidden must not be >n, else not valid (-1)
    //2. bad match (nums[i]==forbidden[i]). ans is at least (bad match+1)/2
    //3. ans is at least max_bad_match_freq
    //greedy algo or boyer-moore-majority vote to find dominant element
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n=nums.size();

        map<int, int> freq;
        map<int, int> badfreq;
        int badmaxfreq=0;
        int cnt=0;
        for(int i=0;i<n;i++){
            freq[nums[i]]++;
            freq[forbidden[i]]++;
            if(freq[nums[i]]>n)
                return -1;
            if(freq[forbidden[i]]>n)
                return -1;
            if(nums[i]==forbidden[i]){
                badfreq[nums[i]]++;
                if(badfreq[nums[i]]>badmaxfreq){
                    badmaxfreq=badfreq[nums[i]];
                }
                cnt++;
            }
        }

        int ret=max((cnt+1)/2,badmaxfreq);

        return ret;
    }
};