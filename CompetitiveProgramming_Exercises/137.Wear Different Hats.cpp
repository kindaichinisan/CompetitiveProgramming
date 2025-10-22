// Number of Ways to Wear Different Hats to Each Other
// There are n people and 40 types of hats labeled from 1 to 40.

// Given a list of integers hats, where hats[i] is a list of all hats preferred by the i-th person.

// Return the number of ways that the n people wear different hats to each other.

// Since the answer may be too large, return it modulo 10^9 + 7.

// Constraints:

// n == hats.length

// 1 <= n <= 10

// 1 <= hats[i].length <= 40

// 1 <= hats[i][j] <= 40

// Example :

// Input: hats = [[3,4],[4,5],[5]]
 
// Output: 1
 
// Explanation: There is only one way to choose hats given the conditions. 
// First person choose hat 3, Second person choose hat 4 and last one hat 5.
//leetcode 1434

//bitmask DP
//n (number of ppl <=10) small
//mask=(person_N-1, ..., person_2, person_1)
//start mask: dp(000) = 1//no one assigned a hat. 1 way
//target mask: dp(111) = ?//evyone assigned a hat.
//000
//Process Hat 3:    000 -> 001 (give hat3 to person 1)
//Process Hat 4:    000 -> 001 (give hat4 to person 1)
//                  000 -> 010 (give hat4 to person 2)
//                  001 -> 011 (give hat4 to person 2, hat3 alredi given to person 1 prev)
//Process Hat 5:    000 -> 010 (give hat5 to person 2)
//                  000 -> 100 (give hat5 to person 3)
//                  001 -> 011 (give hat5 to person 2, hat4 alredi given to person 1 prev)
//                  001 -> 101 (give hat5 to person 3, hat4 alredi given to person 1 prev)
//                  010 -> 110 (give hat5 to person 3, hat4 alredi given to person 2 prev)
//                  011 -> 111 (give hat5 to person 3, hat4 alredi given to person 2 prev, hat3 alredi given to person 1 prev)
class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {

        const int MOD = 1e9 + 7;
        int n = hats.size();

        // Map hat -> list of people who like it
        vector<vector<int>> hatToPeople(41);
        for (int person = 0; person < n; ++person)
            for (int hat : hats[person])
                hatToPeople[hat].push_back(person);

        int totalMasks = 1 << n;
        vector<int> dp(totalMasks, 0);
        dp[0] = 1;  // base: no one has a hat yet

        // Iterate over all hats
        for (int h = 1; h <= 40; ++h) {
            vector<int> new_dp = dp;  // copy current state
            for (int mask = 0; mask < totalMasks; ++mask) {
                if (dp[mask] == 0) continue; //not possible, dont add.
                for (int person : hatToPeople[h]) {
                    if (mask & (1 << person)) continue; // person already has a hat
                    int new_mask = mask | (1 << person);
                    new_dp[new_mask] = (new_dp[new_mask] + dp[mask]) % MOD;
                }
            }
            dp.swap(new_dp);
        }

        return dp[totalMasks - 1];
    }
};