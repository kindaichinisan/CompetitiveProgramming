// Find Two Non-overlapping Sub-arrays Each With Target Sum
// Given an array of integers arr and an integer target.

// You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

// Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.

// Constraints:

// 1 <= arr.length <= 10^5

// 1 <= arr[i] <= 1000

// 1 <= target <= 10^8

// Example:

// Input: arr = [3,1,1,1,5,1,2,1], target = 3
 
// Output: 3
 
// Explanation: Note that sub-arrays [1,2] and [2,1] cannot be an answer because they overlap.

#include<bits/stdc++.h>
using namespace std;

//find 1 subarray which sums to target
//O(N^2). shld use map to store prefixsum to make it O(N)
int minSumOfLength1(vector<int> arr, int target){
    int n=arr.size();
    vector<int> prefixsum(n,0);
    for(int i=0;i<n;i++){
        prefixsum[i+1]=prefixsum[i]+arr[i]; //sum from idx 0 to idx i (inclusive)
    }
    
    vector<int> dp(n, -1); //dp[i]: min length of subarray, considering idx 0 to idx i
    for(int i=0;i<n;i++){
        for(int j=i;j>=0;j--){
            int sum=prefixsum[i+1]-prefixsum[j];//sum from idx j to i (inclusive)
            if(sum==target){
                dp[i]=i-j+1; //update length
            }
            if(sum>=target){
                break;
            }
        }
    }
    
    int min=*min_element(dp.begin(), dp.end());
    
    return min;
}

//find 1 subarray which sums to target
//never use array to store prefixsum, but 1 variable.
//Use map to store prefixsum to make it O(N)
//No dp array too. No need to sort at end. Use min_len.
int minSumOfLength1_1(vector<int> arr, int target){
    int n=arr.size();
    
    map<int, int> prefixIndex;
    
    int prefixsum=0;
    prefixIndex[0] = -1;
    int min1 = INT_MAX;
    for(int i=0;i<n;i++){ //considering element i.
        prefixsum+=arr[i];
        int other_sum=prefixsum-target;
        if(prefixIndex.count(other_sum)){ //find a prefixsum in prev index
            int start=prefixIndex[other_sum]+1;
            int len=i-start+1;
            
            min1=min(min1, len);
        }
        
        prefixIndex[prefixsum] = i; //store the latest idx so as to have min len
    }
    
    return min1;
}

//find 2 subarrays (non-overlapping) which sums to target
//O(N)
int minSumOfLength2_1(vector<int> arr, int target){
    int n=arr.size();
    
    vector<int> best1(n, INT_MAX); //best[i]: min length of subarray, considering idx 0 to idx i
    map<int, int> prefixIndex;
    
    int prefixsum=0;
    prefixIndex[0] = -1;
    int min1=INT_MAX; //store the min len for best subarray
    int min2=INT_MAX; //store the min len for 2 non-overlapping subarray
    for(int i=0;i<n;i++){ //considering element i.
        prefixsum+=arr[i];
        cout<<prefixsum<<endl;
        int other_sum=prefixsum-target;
        cout<<"other_sum: "<<other_sum<<endl;
        if(prefixIndex.count(other_sum)){ //find a prefixsum in prev index
            int start=prefixIndex[other_sum]+1;
            int len=i-start+1;
            
            cout<<"len: "<<len<<endl;
            min1=min(min1, len);
            
            if(start>0 && best1[start-1]!=INT_MAX){ //found the rightmost subarray.
                min2=min(min2, best1[start-1]+len);
            }
            
        }
        
        best1[i]=min1;
        prefixIndex[prefixsum] = i; //store the latest idx so as to have min len
        cout<<"prefixsum: "<<prefixsum<<endl;
    }
    
    if(min2==INT_MAX){
        return -1;
    }
    else{
        return min2;
    }
}

//find 3 subarrays (non-overlapping) which sums to target
//O(N)
int minSumOfLength3_1(vector<int> arr, int target){
    int n=arr.size();
    
    vector<int> best1(n, INT_MAX); //best[i]: min length of subarray, considering idx 0 to idx i
    vector<int> best2(n, INT_MAX); //best[i]: min length of subarray, considering idx 0 to idx i
    map<int, int> prefixIndex;
    
    int prefixsum=0;
    prefixIndex[0] = -1;
    int min1=INT_MAX; //store the min len for best subarray
    int min2=INT_MAX; //store the min len for 2 non-overlapping subarray
    int min3=INT_MAX; //store the min len for 2 non-overlapping subarray
    
    cout<<"min1: "<<min1<<" "<<min2<<" "<<min3<<endl;
    for(int i=0;i<n;i++){ //considering element i.
        prefixsum+=arr[i];
        cout<<prefixsum<<endl;
        int other_sum=prefixsum-target;
        cout<<"other_sum: "<<other_sum<<endl;
        if(prefixIndex.count(other_sum)){ //find a prefixsum in prev index
            int start=prefixIndex[other_sum]+1;
            int len=i-start+1;
            
            min1=min(min1, len);
            
            if(start>0 && best1[start-1]!=INT_MAX){ //found the rightmost subarray.
                min2=min(min2, best1[start-1]+len);
            }
            
            if(start>0 && best2[start-1]!=INT_MAX){ //found the rightmost subarray.
                min3=min(min3, best2[start-1]+len);
            }
            cout<<"len: "<<len<<" "<<min1<<" "<<min2<<" "<<min3<<endl;
            
        }
        
        best1[i]=min1;
        best2[i]=min2;
        prefixIndex[prefixsum] = i; //store the latest idx so as to have min len
        cout<<"prefixsum: "<<prefixsum<<" "<<min1<<" "<<min2<<endl;
    }
    
    if(min3==INT_MAX){
        return -1;
    }
    else{
        return min3;
    }
}

int minSumOfLengths(vector<int> arr, int target) {
    /*arr = {3, 1, 1, 1, 5, 1, 2, 1};
    target=4;
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<target<<endl;*/
    return minSumOfLength2_1(arr, target);
}