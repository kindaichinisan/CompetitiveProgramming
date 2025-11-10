// 3739 Count Subarrays with Majority Elements II
// You are given an integer array nums and an integer target.

// Return the number of subarrays of nums in which target is the majority element.

// The majority element of a subarray is the element that appears strictly more than half of the times in that subarray.

 

// Example 1:

// Input: nums = [1,2,2,3], target = 2

// Output: 5

// Explanation:

// Valid subarrays with target = 2 as the majority element:

// nums[1..1] = [2]
// nums[2..2] = [2]
// nums[1..2] = [2,2]
// nums[0..2] = [1,2,2]
// nums[1..3] = [2,2,3]
// So there are 5 such subarrays.

// Example 2:

// Input: nums = [1,1,1,1], target = 1

// Output: 10

// Explanation:

// ​​​​​​​All 10 subarrays have 1 as the majority element.

// Example 3:

// Input: nums = [1,2,3], target = 4

// Output: 0

// Explanation:

// target = 4 does not appear in nums at all. Therefore, there cannot be any subarray where 4 is the majority element. Hence the answer is 0.

 

// Constraints:

// 1 <= nums.length <= 10​​​​​​​5
// 1 <= nums[i] <= 10​​​​​​​9
// 1 <= target <= 109

// https://leetcode.com/problems/count-subarrays-with-majority-element-ii/

//O(N) soln vs O(N*lgN) soln using segment tree due to consecutive prefix sum differing by 1 only. Able to use array to index.
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n=nums.size();

        vector<int> cnt(2*n+2,0);
        vector<long long> acc(2*n+2,0LL);
        cnt[n+1]=1;
        acc[n+1]=1LL;

        int ps=0;
        long long res=0LL;
        for(int i=0;i<n;i++){
            if(nums[i]==target){
                ps+=1;
            }
            else{
                ps+=-1;
            }
            int idx=n+1+ps;
            cnt[idx]++; //increment the prefix sum
            acc[idx]=acc[idx-1]+cnt[idx]; //compute the acc
            res+=acc[idx-1]; //number of prev subarr less than cur prefix sum
        }

        return res;
    }
};