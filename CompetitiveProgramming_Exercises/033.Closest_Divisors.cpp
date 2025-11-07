// Closest Divisors


// Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.

// Return an array containing the two integers in ascending order.

// Constraints:

// 1 <= num <= 10^9

// Example :

// Input: num = 8
 
// Output: [3,3]
 
// Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.

// https://leetcode.com/problems/closest-divisors/description/

#include<bits/stdc++.h>
using namespace std;

vector<int> closestDivisors_int(int num){
    vector<int> ret;
    for(int i=sqrt(num);i>=1;i--){
        if(num%i==0){
            ret.push_back(i);
            ret.push_back(num/i);
            return ret;
        }
    }
}

vector<int> closestDivisors(int num) {
    vector<int> ret1=closestDivisors_int(num+1);
    vector<int> ret2=closestDivisors_int(num+2);
    int diff1=abs(ret1[0]-ret1[1]);
    int diff2=abs(ret2[0]-ret2[1]);
    if(diff1<diff2){
        return ret1;
    }
    else{
        return ret2;
    }
}