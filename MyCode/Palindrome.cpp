#include<bits/stdc++.h>

using namespace std;

class Palindrome{

    //O(N)
    bool isPalindrome(string s) {
        string t = s;             // make a copy
        reverse(t.begin(), t.end()); // reverse the copy
        return s == t;            // check equality
    }

    //precompute palindrome table for all possible substrings of s
    //O(N^2). DP
    vector<vector<bool>> precomputePalindromeTable(string s){

        int n=s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        for(int l = n-1; l >= 0; l--) {
            for(int r = l; r < n; r++) {
                if(s[l] == s[r] && (r-l <= 1 || isPal[l+1][r-1]))
                    isPal[l][r] = true;
            }
        }

        return isPal;
    }

    //precompute palindrome table for all possible substrings of s
    //O(N). Manacher’s algorithm
    //^: start sentinel
    //$: end sentinel
    //#: between all letters and sentinel. Convert all string to odd len string. unify odd and even len palindrome.
    //number of #=strlen-1. strlen + strlen -1 = odd number
    vector<vector<bool>> precomputePalindromeTable(const string &s) {
        int n = s.size();
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        if (n == 0) return isPal;

        // Build transformed string: ^#a#b#c#...#$
        string t = "^";
        for (char c : s) {
            t += "#" + string(1, c);
        }
        t += "#$";

        int m = t.size();
        vector<int> P(m, 0);
        int center = 0, right = 0;

        // Manacher: compute P array
        for (int i = 1; i < m - 1; ++i) {
            if (i < right){ //i inside rightmost palindrome
                //P[mirror]: left palindrome fits fully inside the right boundary), we can safely copy it.
                //right - i: mirror palindrome goes beyond the left boundary), we can only use up to the current right boundary
                int mirror = 2 * center - i;
                P[i] = min(right - i, P[mirror]); //palindrome radius of idx i
            }
            while (t[i + 1 + P[i]] == t[i - 1 - P[i]]){ //expand outward beyond right if possible
                ++P[i];
            }
            if (i + P[i] > right) { //if cur idx palindrome is righter than rightmost palindrome
                center = i;
                right = i + P[i];
            }
        }

        // Map palindromic spans in t back to isPal in s
        for (int i = 1; i < m - 1; ++i) {
            for (int k = 1; k <= P[i]; ++k) {
                int L = i - k;
                int R = i + k;
                // Map to original string indices
                int l = (L - 1) / 2; // integer division floors
                int r = (R - 2) / 2;
                if (l >= 0 && r < n && l <= r) {
                    isPal[l][r] = true;
                }
            }
        }

        return isPal;
    }
};