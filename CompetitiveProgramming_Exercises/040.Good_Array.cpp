// Good Array


// Given an array nums of positive integers. Your task is to select some subset of nums, multiply each element by an integer and add all these numbers. The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.

// Return True if the array is good otherwise return False.

// Constraints:

// 1 <= nums.length <= 10^5

// 1 <= nums[i] <= 10^9

// Example :

// Input: nums = [12,5,7,23]
 
// Output: true
 
// Explanation: Pick numbers 5 and 7.
// 5*3 + 7*(-2) = 1

// https://leetcode.com/problems/check-if-it-is-a-good-array/description/

// find the gcd of the list of number. If 1, true. Bezout's Identity.
// qn ask to find subset of number whose gcd=1.
// if subset of number gcd=1, list of number gcd=1
#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int gcd(vector<int> nums){
    int g=0;
    for(int i=0;i<nums.size();i++){
        g=gcd(g, nums[i]);
    }
    return g;
}
    
bool isGoodArray(vector<int> nums) {
    int g=gcd(nums);
    
    return g==1;
}