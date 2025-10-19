// Count All Possible Routes
// You are given an array of distinct positive integers locations where locations[i] represents the position of city i. You are also given integers start, finish and fuel representing the starting city, ending city, and the initial amount of fuel you have, respectively.

// At each step, if you are at city i, you can pick any city j such that j != i and 0 <= j < locations.length and move to city j. Moving from city i to city j reduces the amount of fuel you have by |locations[i] - locations[j]|. Please notice that |x| denotes the absolute value of x.

// Notice that fuel cannot become negative at any point in time, and that you are allowed to visit any city more than once (including start and finish).

// Return the count of all possible routes from start to finish.

// Since the answer may be too large, return it modulo 10^9 + 7.

// Constraints:

// 2 <= locations.length <= 100

// 1 <= locations[i] <= 10^9

// All integers in locations are distinct.

// 0 <= start, finish < locations.length

// 1 <= fuel <= 200

// Example:

// Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
 
// Output: 4
 
// Explanation: The following are all possible routes, each uses 5 units of fuel:
// 1 -> 3
// 1 -> 2 -> 3
// 1 -> 4 -> 3
// 1 -> 4 -> 2 -> 3
//leetcode 1575

#include<bits/stdc++.h>
using namespace std;

//O(N^2*fuel)
//must use finish all fuel. Not clear in question.
//dp[i][j]: number of routes to reach city i with fuel j
//with the cout results in TLE. w/o cout, Accepted. beat 5%
int countRoutes(vector<int> locations, int start, int finish, int fuel) {
    int n=locations.size();
    
    //for(int i=0;i<n;i++){
        //cout<<locations[i]<<" ";
    //}
    //cout<<endl;
    //cout<<start<<" "<<finish<<" "<<fuel<<endl;
    
    const int mod=1000000007;
    
    //cout<<"precompute"<<endl;
    //precompute
    vector<vector<long long>> consumption(n,vector<long long>(n,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            consumption[i][j]=abs(locations[i]-locations[j]);
            //cout<<consumption[i][j]<<" ";
        }
        //cout<<endl;
    }
    
    //cout<<"dp"<<endl;
    vector<vector<int>> dp(n, vector<int>(fuel+1,0));
    dp[start][fuel]=1;
    for(int ff=fuel-1;ff>=0;ff--){
        //cout<<"fuel "<<ff<<endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    int ini_fuel=ff+consumption[i][j];
                    if(ini_fuel<=fuel){
                        dp[i][ff]+=dp[j][ini_fuel];
                        dp[i][ff]%=mod;
                    }
                }
                //cout<<dp[i][ff]<<" ";
            }
            //cout<<endl;
        }
    }
    
    long long sum=0;
    for(int i=0;i<fuel;i++){
        sum+=dp[finish][i];
        sum%=mod;
    }
    
    if(start==finish){
        sum=(sum+1)%mod;
    }
    return (int)sum;
    
    
}

//faster method without decrementing fuel 1 by 1. beat 18%
int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
    const int MOD = 1e9 + 7;
    int n = locations.size();
    vector<vector<int>> dp(n, vector<int>(fuel + 1, -1));

    function<int(int, int)> dfs = [&](int i, int f) -> int {
        if (f < 0) return 0;
        if (dp[i][f] != -1) return dp[i][f];
        long long ans = (i == finish) ? 1 : 0;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            int cost = abs(locations[i] - locations[j]);
            if (f >= cost)
                ans += dfs(j, f - cost);
        }
        return dp[i][f] = ans % MOD;
    };

    return dfs(start, fuel);
}

//fastest beats 93%. recursion method.
int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
    constexpr int MOD = 1'000'000'007;
    const int n = locations.size();

    // Precompute all pairwise distances once
    static int dist[100][100];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = abs(locations[i] - locations[j]);

    // Initialize memoization table with -1
    vector<vector<int>> dp(n, vector<int>(fuel + 1, -1));

    auto dfs = [&](auto&& self, int i, int f) -> int {
        if (f < 0) return 0;
        int& res = dp[i][f];
        if (res != -1) return res;

        long long ans = (i == finish);
        const int* d = dist[i];  // pointer for cache locality
        for (int j = 0; j < n; ++j) {
            int cost = d[j];
            if (cost > 0 && f >= cost) {
                ans += self(self, j, f - cost);
                if (ans >= MOD) ans -= MOD;  // avoid overflow
            }
        }

        return res = static_cast<int>(ans);
    };

    return dfs(dfs, start, fuel);
}

//iteration method beat 98%. similar to my way
int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
    constexpr int MOD = 1'000'000'007;
    const int n = locations.size();

    // Precompute pairwise distances
    static int dist[100][100];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = abs(locations[i] - locations[j]);

    // dp[i][f] = ways to reach city i with exactly f fuel used
    vector<vector<int>> dp(n, vector<int>(fuel + 1, 0));
    dp[start][0] = 1;

    for (int f = 0; f <= fuel; ++f) {
        for (int i = 0; i < n; ++i) {
            int ways = dp[i][f];
            if (!ways) continue; //if 0 means cannot reach city i
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                int cost = dist[i][j];
                if (f + cost <= fuel) {
                    dp[j][f + cost] += ways;
                    if (dp[j][f + cost] >= MOD) dp[j][f + cost] -= MOD; //use > and - instead of %
                }
            }
        }
    }

    long long ans = 0;
    for (int f = 0; f <= fuel; ++f) {
        ans += dp[finish][f];
        if (ans >= MOD) ans -= MOD;
    }

    return static_cast<int>(ans);
}