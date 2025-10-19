// Palindrome Partitioning
// Given a string s, partition s such that every substring of the partition is a palindrome.

// Return the minimum cuts needed for a palindrome partitioning of s.

// Constraints:

// 1 <= s.length <= 2000

// s consists of lower-case English letters only.

// Example:

// Input: s = "aab"
 
// Output: 1
 
// Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

//leetcode 132

// O(N^3) lead to TLE
// dp[l][r]: min number of palindrome cuts for s[l...r]
// optimization: precompute palindrome table O(N^2)
// diff formulation dp[i]: min cuts for s[0...i]
// #include<bits/stdc++.h>
// using namespace std;

// int dpFn(string& s, int l, int r, vector<vector<int>>& memo){
//     int str_len=r-l+1;
//     if(str_len==1) //1 letter is palindrome
//         return 0;
//     int& ans=memo[l][r];
//     if(ans!=INT_MAX){
//         return ans;
//     }
        
//     bool pal=true;
//     for(int i=0;i<=str_len/2;i++){
//         if(s[l+i]!=s[r-i]){
//             pal=false;
//             break;
//         }
//     }
//     if(pal)
//         return 0;
        
//     for(int i=l;i<r;i++){
//         ans=min(ans,dpFn(s,l,i,memo)+dpFn(s,i+1,r,memo)+1);
//         //cout<<l<<" "<<r<<" "<<i<<endl;
//         //cout<<dpFn(s,l,i,memo)+dpFn(s,i+1,r,memo)+1<<endl;
//     }
    
    
//     return ans;
// }

// //dp[l][r]: min number of palindrome cuts 
// int minCut(string s) {
    
//     int n=s.size();
    
//     vector<vector<int>> memo(n, vector<int>(n,INT_MAX));
    
//     return dpFn(s, 0, n-1, memo);

    
// }

//optimize O(N^2)
#include<bits/stdc++.h>
using namespace std;

vector<vector<bool>> precomputePalindromeTable(string s){

    int n=s.size();
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    for(int i = n-1; i >= 0; i--) {
        for(int j = i; j < n; j++) {
            if(s[i] == s[j] && (j-i <= 1 || isPal[i+1][j-1]))
                isPal[i][j] = true;
        }
    }

    return isPal;
}

int minCut(string s) {

    int n=s.size();

    vector<vector<bool>> isPal = precomputePalindromeTable(s);
    
    vector<int> dp(n, INT_MAX);
    for(int i = 0; i < n; i++) {
        if(isPal[0][i]) dp[i] = 0;
        else {
            for(int j = 0; j < i; j++) {
                if(isPal[j+1][i]) //check the rightmost substring is palindrome, then is valid. leftmost substr is ensured to be palindrome by dp[i]
                    dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }

    return dp[n-1];
}