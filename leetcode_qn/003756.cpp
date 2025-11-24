// 3756. Concatenate Non-Zero Digits and Multiply by Sum II

// You are given a string s of length m consisting of digits. You are also given a 2D integer array queries, where queries[i] = [li, ri].

// For each queries[i], extract the substring s[li..ri]. Then, perform the following:

// Form a new integer x by concatenating all the non-zero digits from the substring in their original order. If there are no non-zero digits, x = 0.
// Let sum be the sum of digits in x. The answer is x * sum.
// Return an array of integers answer where answer[i] is the answer to the ith query.

// Since the answers may be very large, return them modulo 109 + 7.

 

// Example 1:

// Input: s = "10203004", queries = [[0,7],[1,3],[4,6]]

// Output: [12340, 4, 9]

// Explanation:

// s[0..7] = "10203004"
// x = 1234
// sum = 1 + 2 + 3 + 4 = 10
// Therefore, answer is 1234 * 10 = 12340.
// s[1..3] = "020"
// x = 2
// sum = 2
// Therefore, the answer is 2 * 2 = 4.
// s[4..6] = "300"
// x = 3
// sum = 3
// Therefore, the answer is 3 * 3 = 9.
// Example 2:

// Input: s = "1000", queries = [[0,3],[1,1]]

// Output: [1, 0]

// Explanation:

// s[0..3] = "1000"
// x = 1
// sum = 1
// Therefore, the answer is 1 * 1 = 1.
// s[1..1] = "0"
// x = 0
// sum = 0
// Therefore, the answer is 0 * 0 = 0.
// Example 3:

// Input: s = "9876543210", queries = [[0,9]]

// Output: [444444137]

// Explanation:

// s[0..9] = "9876543210"
// x = 987654321
// sum = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
// Therefore, the answer is 987654321 * 45 = 44444444445.
// We return 44444444445 modulo (109 + 7) = 444444137.
 

// Constraints:

// 1 <= m == s.length <= 105
// s consists of digits only.
// 1 <= queries.length <= 105
// queries[i] = [li, ri]
// 0 <= li <= ri < m

// https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/description/

// O(s.size() + queries.size())
// int x=((pd[r+1]-(ll)pd[l]*tenmod[num_not])%mod+mod)%mod;
// put ll at the pd[l] as it multiplies with tenmod first. Both are not ll. May overflow.
// after -, bracket the whole th and %mod (may get negative vle), then +mod, and %mod again.
#define ll long long

class Solution {
public:

    const int mod=1e9+7;
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n=s.size();

        vector<int> ps(n+1,0);
        vector<int> pd(n+1,0);
        vector<int> tenmod(n+1,1);
        vector<int> num_not0(n+1,0);

        for(int i=0;i<n;i++){
            int num=s[i]-'0';
            ps[i+1]=((ll)ps[i]+num)%mod;
            if(num!=0){
                pd[i+1]=(pd[i]*10LL+num)%mod;
                num_not0[i+1]=num_not0[i]+1;
            }
            else{
                pd[i+1]=pd[i];
                num_not0[i+1]=num_not0[i];
            }
            tenmod[i+1]=(tenmod[i]*10LL)%mod;
        }

        // for(int i=0;i<n+1;i++){
        //     cout<<num_not0[i]<<" ";
        // }
        // cout<<endl;

        // cout<<"tenmod"<<endl;
        // for(int i=0;i<n+1;i++){
        //     cout<<tenmod[i]<<" ";
        // }
        // cout<<endl;

        // cout<<"pd"<<endl;
        // for(int i=0;i<n+1;i++){
        //     cout<<pd[i]<<" ";
        // }
        // cout<<endl;

        int m=queries.size();

        vector<int> ret_list;
        for(int i=0;i<m;i++){
            //cout<<"query: "<<i<<endl;
            int l=queries[i][0];
            int r=queries[i][1];
            int sum=(ps[r+1]-ps[l]+mod)%mod;
            //cout<<sum<<endl;
            int num_not=num_not0[r+1]-num_not0[l];
            //cout<<"num_not: "<<num_not<<endl;
            //cout<<pd[r+1]<<endl;
            //cout<<pd[l]<<endl;
            int x=((pd[r+1]-(ll)pd[l]*tenmod[num_not])%mod+mod)%mod;
            //cout<<"x: "<<x<<endl;
            int ret=((ll)x*sum)%mod;
            ret_list.push_back(ret);
        }

        return ret_list;
    }
};