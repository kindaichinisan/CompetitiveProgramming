// Best Time to Buy and Sell Stock
// You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

// Find the maximum profit you can achieve. You may complete at most k transactions.

// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

// Constraints:

// 0 <= k <= 100

// 0 <= prices.length <= 1000

// 0 <= prices[i] <= 1000


// Example :

// Input: k = 2, prices = [2,4,1]
 
// Output: 2
 
// Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

#include<bits/stdc++.h>
using namespace std;

int maxProfit(int k, vector<int> prices) {
    int n=prices.size();

    if(k==0){ //no transactions
        return 0;
    }
    
    if(n==0){ //no prices
        return 0;
    }
    
    if(k>=n/2){ //can buy and sell as many times as possible. use greedy approach
        int profit=0;
        for(int i=1;i<n;i++){
            int consecutive_day_profit=prices[i]-prices[i-1];
            if(consecutive_day_profit>0){
                profit+=consecutive_day_profit;
            }
        }
        return profit;
    }
    
    //use DP
    //dp[t][i]=max profit up to day i (including) using up to t transactions
    //dp[t][i]=max(dp[t][i-1], //dont do anyth on day i
    //              prices[i]-max_diff //sell on day i. max_diff is (t-1) transactions + 1 buy transaction b4 day i
    //max_diff=max(dp[t-1][j]-prices[j]) for j=0 to i
    
    vector<vector<int>> dp(k+1, vector<int>(n, 0));
    for(int kk=1;kk<=k;kk++){ //use 1 transactions, then 2, then 3, etc.
        int max_diff=-prices[0];
        for(int nn=1;nn<n;nn++){ //on day 1 (day is 0-idx)
            dp[kk][nn]=max(dp[kk][nn-1], prices[nn]+max_diff);
            max_diff=max(max_diff, dp[kk-1][nn-1]-prices[nn]); //this is more intuitive.
            //max_diff=max(max_diff, dp[kk-1][nn]-prices[nn]); //WJ:weird that this soln can work with either
        }
    }
    
    return dp[k][n-1];
}