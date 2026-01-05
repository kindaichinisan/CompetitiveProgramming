// 3795. Minimum Subarray Length With Distinct Sum At Least K

// You are given an integer array nums and an integer k.

// Return the minimum length of a subarray whose sum of the distinct values present in that subarray (each value counted once) is at least k. If no such subarray exists, return -1.

 

// Example 1:

// Input: nums = [2,2,3,1], k = 4

// Output: 2

// Explanation:

// The subarray [2, 3] has distinct elements {2, 3} whose sum is 2 + 3 = 5, which is ​​​​​​​at least k = 4. Thus, the answer is 2.

// Example 2:

// Input: nums = [3,2,3,4], k = 5

// Output: 2

// Explanation:

// The subarray [3, 2] has distinct elements {3, 2} whose sum is 3 + 2 = 5, which is ​​​​​​​at least k = 5. Thus, the answer is 2.

// Example 3:

// Input: nums = [5,5,4], k = 5

// Output: 1

// Explanation:

// The subarray [5] has distinct elements {5} whose sum is 5, which is at least k = 5. Thus, the answer is 1.

 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 105
// 1 <= k <= 109

#define ll long long

class Solution {
public:
    int minLength(vector<int>& nums, int k) {

        vector<int> temp;
        int n=nums.size();
        // temp.push_back(nums[0]);
        // for(int i=0;i<n-1;i++){
        //     if(nums[i]!=nums[i+1])
        //         temp.push_back(nums[i+1]);
        // }

        // n=temp.size();
        // nums=temp;

        unordered_map<int, int> freq;

        ll sum=0LL;
        int cur_L=-1;
        int minL=-1;
        int endpt=0;
        for(int i=0;i<n;i++){
            if(i>0){
                freq[nums[i-1]]--;
                
                if(freq[nums[i-1]]==0){
                    sum-=nums[i-1];
                }

                if(sum>=k){
                    cur_L--;
                    minL=min(minL, cur_L);
                }
            }
            if(sum<k){
                for(int j=endpt;j<n;j++){
                    freq[nums[j]]++;
                    if(freq[nums[j]]==1){
                        sum+=nums[j];
                    }
                    if(sum>=k){
                        cur_L=j-i+1;
                        
                        endpt=j+1;
                        cout<<cur_L<<endl;

                        if(minL==-1){
                            minL=cur_L;
                        }
                        else{
                            minL=min(minL, cur_L);
                        }
                        break;
                    }
                    if(j==n-1)
                        return minL;
                }
                
            }

            if(minL==1)
                return 1;

        }

        return minL;
    }
};

// https://leetcode.com/problems/minimum-subarray-length-with-distinct-sum-at-least-k/solutions/7462722/javacpython-sliding-window-by-lee215-y3cr/
// this soln explains about right window expansion and left window contraction very well
// compact code