// 3854. Minimum Operations to Make Array Parity Alternating

// You are given an integer array nums.

// An array is called parity alternating if for every index i where 0 <= i < n - 1, nums[i] and nums[i + 1] have different parity (one is even and the other is odd).

// In one operation, you may choose any index i and either increase nums[i] by 1 or decrease nums[i] by 1.

// Return an integer array answer of length 2 where:

// answer[0] is the minimum number of operations required to make the array parity alternating.
// answer[1] is the minimum possible value of max(nums) - min(nums) taken over all arrays that are parity alternating and can be obtained by performing exactly answer[0] operations.
// An array of length 1 is considered parity alternating.

 

// Example 1:

// Input: nums = [-2,-3,1,4]

// Output: [2,6]

// Explanation:

// Applying the following operations:

// Increase nums[2] by 1, resulting in nums = [-2, -3, 2, 4].
// Decrease nums[3] by 1, resulting in nums = [-2, -3, 2, 3].
// The resulting array is parity alternating, and the value of max(nums) - min(nums) = 3 - (-3) = 6 is the minimum possible among all parity alternating arrays obtainable using exactly 2 operations.

// Example 2:

// Input: nums = [0,2,-2]

// Output: [1,3]

// Explanation:

// Applying the following operation:

// Decrease nums[1] by 1, resulting in nums = [0, 1, -2].
// The resulting array is parity alternating, and the value of max(nums) - min(nums) = 1 - (-2) = 3 is the minimum possible among all parity alternating arrays obtainable using exactly 1 operation.

// Example 3:

// Input: nums = [7]

// Output: [0,0]

// Explanation:

// No operations are required. The array is already parity alternating, and the value of max(nums) - min(nums) = 7 - 7 = 0, which is the minimum possible.

 

// Constraints:

// 1 <= nums.length <= 105
// -109 <= nums[i] <= 109

class Solution {
public:

    void changeOddIdxEven(vector<int> nums, int n, int maxi, int mini, int& num_opr, int& diff){
        
        num_opr=0;
        for(int i=0;i<n;i++){
            if(i%2==1){ //odd idx
                if(nums[i]%2!=0){
                    cout<<i<<endl;
                    if((nums[i]==maxi) && (nums[i]==mini)){
                        nums[i]++;
                    }
                    else if(nums[i]==maxi){
                        nums[i]--;
                    }
                    else if(nums[i]==mini){
                        nums[i]++;
                    }
                    num_opr++;
                }
            }
            else{ //even idx
                if(nums[i]%2==0){
                    cout<<i<<endl;
                    if((nums[i]==maxi) && (nums[i]==mini)){
                        nums[i]++;
                    }
                    else if(nums[i]==maxi){
                        nums[i]--;
                    }
                    else if(nums[i]==mini){
                        nums[i]++;
                    }
                    num_opr++;
                }
            }
        }
        maxi=*max_element(nums.begin(), nums.end());
        mini=*min_element(nums.begin(), nums.end());
        diff = maxi-mini;
    }

    void changeEvenIdxEven(vector<int> nums, int n, int maxi, int mini, int& num_opr, int& diff){
        
        num_opr=0;
        for(int i=0;i<n;i++){
            if(i%2==0){ //even idx
                if(nums[i]%2!=0){
                    if((nums[i]==maxi) && (nums[i]==mini)){
                        nums[i]++;
                    }
                    else if(nums[i]==maxi){
                        nums[i]--;
                    }
                    else if(nums[i]==mini){
                        nums[i]++;
                    }
                    num_opr++;
                }
            }
            else{ //odd idx
                if(nums[i]%2==0){
                    if((nums[i]==maxi) && (nums[i]==mini)){
                        nums[i]++;
                    }
                    else if(nums[i]==maxi){
                        nums[i]--;
                    }
                    else if(nums[i]==mini){
                        nums[i]++;
                    }
                    num_opr++;
                }
            }
        }
        maxi=*max_element(nums.begin(), nums.end());
        mini=*min_element(nums.begin(), nums.end());
        diff = maxi-mini;
    }

    vector<int> makeParityAlternating(vector<int>& nums) {
        int n=nums.size();
        int num_opr1=0;
        int num_opr2=0;
        int diff1=-1;
        int diff2=-1;

        int maxi=*max_element(nums.begin(), nums.end());
        int mini=*min_element(nums.begin(), nums.end());

        changeOddIdxEven(nums, n, maxi, mini, num_opr1, diff1);
        cout<<num_opr1<<" "<<diff1<<endl;
        changeEvenIdxEven(nums, n, maxi, mini, num_opr2, diff2);
        cout<<num_opr2<<" "<<diff2<<endl;

        if(num_opr1<num_opr2){
            return {num_opr1,diff1};
        }
        else if(num_opr2<num_opr1){
            return {num_opr2,diff2};
        }
        else{
            if(diff1<diff2){
                return {num_opr1,diff1};
            }
            else{
                return {num_opr2,diff2};
            }
        }
    }
};