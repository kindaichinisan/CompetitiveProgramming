// 3844. Longest Almost-Palindromic Substring
// You are given a string s consisting of lowercase English letters.

// A substring is almost-palindromic if it becomes a palindrome after removing exactly one character from it.

// Return an integer denoting the length of the longest almost-palindromic substring in s.

 

// Example 1:

// Input: s = "abca"

// Output: 4

// Explanation:

// Choose the substring "abca".

// Remove "abca".
// The string becomes "aba", which is a palindrome.
// Therefore, "abca" is almost-palindromic.
// Example 2:

// Input: s = "abba"

// Output: 4

// Explanation:

// Choose the substring "abba".

// Remove "abba".
// The string becomes "aba", which is a palindrome.
// Therefore, "abba" is almost-palindromic.
// Example 3:

// Input: s = "zzabba"

// Output: 5

// Explanation:

// Choose the substring "zzabba".

// Remove "zabba".
// The string becomes "abba", which is a palindrome.
// Therefore, "zabba" is almost-palindromic.
 

// Constraints:

// 2 <= s.length <= 2500
// s consists of only lowercase English letters.
// https://leetcode.com/problems/longest-almost-palindromic-substring/description/

//hard to get logic correct.
//a different way to get palindrome which allows skip index to get "almost palindrome" len.
class Solution {
public:

    int expand_skip_left(const string& s, int n, int left, int right){
        
        bool skipped = false;  // exactly one skip allowed
        int l = left, r = right;

        int len=0;
        while (l >= 0 && r < n) {
            if (s[l] == s[r]) {
                if (skipped){
                    len=r-l+1;
                }
            } else {
                if (skipped) break;  // already skipped one
                // Try skipping left OR right exactly once
                if (l-1>=0) {
                    l--;  // skip left
                    if(s[l]==s[r]){
                        len=r-l+1;
                    }
                    else {
                        l++;
                        r--;
                        len=r-l+1;
                        break;  // cannot match even with one skip
                    }
                }
                else{ //cannot expand left
                    len=r-l;
                    break;
                }
                
                skipped = true;
            }
            if((l==0) || (r==n-1))//stop if reach end
            {
                if(skipped){
                    len=r-l+1;
                }
                else{
                    if(l>0){
                        l--;
                        len=r-l+1;
                    }
                }
                break;
            }
            l--;
            r++;
        }
        return len;  // length of palindrome after exactly one removal
    }

    int expand_skip_right(const string& s, int n, int left, int right){
        
        bool skipped = false;  // exactly one skip allowed
        int l = left, r = right;

        int len=0;
        while (l >= 0 && r < n) {
            if (s[l] == s[r]) {
                if (skipped){
                    len=r-l+1;
                }
            } else {
                if (skipped) break;  // already skipped one
                // Try skipping left OR right exactly once
                skipped = true;
                if (r+1<n) {
                    r++;  // skip left
                    if(s[l]==s[r]){
                        len=r-l+1;
                    }
                    else {
                        l++;
                        r--;
                        len=r-l+1;
                    }
                }
                else{ //cannot expand right
                    len=r-l;
                    break;
                }
                
            }
            if((l==0) || (r==n-1))//stop if reach end
            {
                if(skipped){
                    len=r-l+1;
                }
                else{
                    if(r+1<n){
                        r++;
                        len=r-l+1;
                    }
                }
                break;
            }
            l--;
            r++;
        }
        return len;  // length of palindrome after exactly one removal
    }
    
    int longestAlmostPalindrome(const string &s) {
        int n = s.size();
        int max_len = 0;
    
    
        for (int i = 0; i < n; i++) {
            int len=expand_skip_left(s, n, i, i);
            max_len = max(max_len, len);     // odd-length center
            len=expand_skip_right(s, n, i, i);
            max_len = max(max_len, len);     // odd-length center
            len=expand_skip_left(s, n, i, i+1);
            max_len = max(max_len, len);   // even-length center
            len=expand_skip_right(s, n, i, i+1);
            max_len = max(max_len, len);   // even-length center
        }
    
        return max_len;
    }
    
    //remove each character and find the longest palindrome
    int almostPalindromic(string s) {
        int n=s.size();

        // int max_len=0;
        // for(int i=0;i<n;i++){
        //     string s2=s;
        //     s2.erase(i,1); //find length of pal in s2.

        //     int len= precomputePalindromeTable2(s2);

        //     if(max_len<len){
        //         max_len=len;
        //     }
        // }

        // return max_len+1;

        return longestAlmostPalindrome(s);
    }
};