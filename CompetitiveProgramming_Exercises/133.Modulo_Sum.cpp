// Modulo Sum
// You are given a sequence of numbers a1, a2, ..., an, and a number m.

// Check if it is possible to choose a non-empty subsequence of a such that the sum of numbers in this subsequence is divisible by m.

// Return "Yes" if there exists the sought subsequence otherwise "No" without the quotes.

// Constraints:

// 1 <= n <= 10^6

// 2 <= m <= 10^3

// 0 <= ai <= 10^9

// Example :

// Input:  n = 3, m = 5, a = {1, 2, 3}
 
// Output: Yes
 
// Explanation:  You can choose numbers 2 and 3, the sum of which is divisible by 5.
//Codeforces 577B

#include<bits/stdc++.h>
using namespace std;

//bool dp[i][j]: able to use first ith number to modulo j when divided by m
//dp[i][j]=dp[i-1][j] || //dont use ith number
//            dp[i-1][j-a[i]] //use ith number
//j: 0 to m-1 (1e3)
//i: 0 to n (1e6)
//O(MN) this will TLE as N is large. Use pigeon hole principle to reduce to O(M^2)
//can optimize space to use 1D array instead of 2D array
// fastest. 1421 ms
// string solve(int n,int m,vector<int> a){

//     if(n>=m)
//         return "Yes"; //pigeon hole principle. change from O(NM) to O(M^2)
    
//     vector<vector<bool>> dp(n+1, vector<bool>(m,false)); //not possible
    
//     //dp[1][a[0]%m]=true;
//     for(int i=0;i<n;i++){
//         for(int j=0;j<m;j++){
//             if(j==a[i]%m){
//                 dp[i+1][j]=true;
//             }
//             else{
//                 int prev_modulo=(j+m-a[i]%m)%m;
//                 dp[i+1][j]=dp[i][j] || dp[i][prev_modulo];
//             }
//         }
//     }
    
//     if(dp[n][0])
//         return "Yes";
//     else
//         return "No";
// }

//use 1D array
//early termination
//slow due to creating a new vector<bool> dp on every iteration (which causes memory copying and cache misses). 1468 ms
// string solve(int n, int m, vector<int>& a) {
//     // Pigeonhole principle shortcut
//     if (n >= m) return "Yes";

//     vector<bool> dp(m, false);
//     for (int x : a) {
//         vector<bool> newdp = dp;
//         int r = x % m;
//         newdp[r] = true;  // use single element

//         for (int i = 0; i < m; ++i)
//             if (dp[i])
//                 newdp[(i + r) % m] = true;

//         dp = newdp;

//         if (dp[0]) return "Yes"; // found divisible subset
//     }

//     return dp[0] ? "Yes" : "No";
// }

//Bitset optimization (super fast version) not as fast as expected. 1437 ms
string solve(int n, int m, vector<int>& a) {
    if (n >= m) return "Yes";  // Pigeonhole principle

    bitset<1000> dp;
    for (int x : a) {
        int r = x % m;
        dp |= (dp << r) | (dp >> (m - r)); // circular shift
        dp[r] = 1;
        if (dp[0]) return "Yes";
    }
    return "No";
}

int main(){
    int n,m;
    cin>>n>>m;

    vector<int> a(n,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    string ans=solve(n, m, a);
    cout<<ans<<endl;
}