// Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

 

// Example 1:

// Input: nums = [1,2,3,4,5,6,7], k = 3
// Output: [5,6,7,1,2,3,4]
// Explanation:
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]
// Example 2:

// Input: nums = [-1,-100,3,99], k = 2
// Output: [3,99,-1,-100]
// Explanation: 
// rotate 1 steps to the right: [99,-1,-100,3]
// rotate 2 steps to the right: [3,99,-1,-100]
 

// Constraints:

// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1
// 0 <= k <= 105
 

// Follow up:

// Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
// Could you do it in-place with O(1) extra space?

class Solution {
public:
    //need to be careful and trial and error.
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();

        k=k%n;

        int cnt=0; //to stop if reach end
        int idx=0; //to keep idx
        int start_idx=idx;

        int temp[2]; //temp buffer
        temp[cnt%2]=nums[idx]; //from
        while(cnt<n){
            temp[(cnt+1)%2]=nums[(idx+k)%n]; //to
            nums[(idx+k)%n]=temp[cnt%2];
            idx=(idx+k)%n;
            
            if(idx==start_idx){
                idx=(idx+1)%n;
                start_idx=idx;
                temp[(cnt+1)%2]=nums[start_idx];
            }
            cnt++;
        }
    }

    //smart way to use 3 reverse.
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();

        k=k%n;

        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }
};