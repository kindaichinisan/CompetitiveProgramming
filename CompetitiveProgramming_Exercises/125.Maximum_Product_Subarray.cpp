// Maximum Product Subarray
// Given an integer array nums, find a contiguous non-empty subarray within the array that has the largest product, and return the product.

// It is guaranteed that the answer will fit in a 32-bit integer. A subarray is a contiguous subsequence of the array.

// Constraints:

// 1 <= nums.length <= 2 * 10^4

// -10 <= nums[i] <= 10

// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

// Example:

// Input: nums = [2,3,-2,4]
 
// Output: 6
 
// Explanation: [2,3] has the largest product 6.

#include<bits/stdc++.h>
using namespace std;


//dp[i] is the largest pdt when using ith element
//dp2[i] is the largest pdt when using up to ith element
//dp2[i+1]=max(dp[i] (dont use (i+1)th element), dp[i]*nums[i+1] (use (i+1)th element)
//ans=max(dp2[nums.size()-1]
//use 2 array of min and max pdt instead of local variables as it will be modified wrongly.
int maxProduct(vector<int> nums) {
    
    
    int n=nums.size();
    
    
    for(int i=0;i<n;i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    vector<int> max_pdt_list(n,0);
    vector<int> min_pdt_list(n,0);
    max_pdt_list[0]=nums[0];
    min_pdt_list[0]=nums[0];
    
    for(int i=1;i<n;i++){
        if(nums[i]>=0){
            max_pdt_list[i]=max(max_pdt_list[i-1]*nums[i], nums[i]);
            min_pdt_list[i]=min(min_pdt_list[i-1]*nums[i], nums[i]);
        }
        else{
            min_pdt_list[i]=min(max_pdt_list[i-1]*nums[i], nums[i]);
            max_pdt_list[i]=max(min_pdt_list[i-1]*nums[i], nums[i]);
        }
    }
    
    for(int i=0;i<max_pdt_list.size();i++){
        cout<<max_pdt_list[i]<<" ";
    }
    cout<<endl;
    int max=*max_element(max_pdt_list.begin(), max_pdt_list.end());
    
    return max;
    
}