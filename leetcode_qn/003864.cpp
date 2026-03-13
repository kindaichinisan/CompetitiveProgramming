// 3864. Minimum Cost to Partition a Binary String
// You are given a binary string s and two integers encCost and flatCost.

// For each index i, s[i] = '1' indicates that the ith element is sensitive, and s[i] = '0' indicates that it is not.

// The string must be partitioned into segments. Initially, the entire string forms a single segment.

// For a segment of length L containing X sensitive elements:

// If X = 0, the cost is flatCost.
// If X > 0, the cost is L * X * encCost.
// If a segment has even length, you may split it into two contiguous segments of equal length and the cost of this split is the sum of costs of the resulting segments.

// Return an integer denoting the minimum possible total cost over all valid partitions.

 

// Example 1:

// Input: s = "1010", encCost = 2, flatCost = 1

// Output: 6

// Explanation:

// The entire string s = "1010" has length 4 and contains 2 sensitive elements, giving a cost of 4 * 2 * 2 = 16.
// Since the length is even, it can be split into "10" and "10". Each segment has length 2 and contains 1 sensitive element, so each costs 2 * 1 * 2 = 4, giving a total of 8.
// Splitting both segments into four single-character segments yields the segments "1", "0", "1", and "0". A segment containing "1" has length 1 and exactly one sensitive element, giving a cost of 1 * 1 * 2 = 2, while a segment containing "0" has no sensitive elements and therefore costs flatCost = 1.
// ​​​​​​​The total cost is thus 2 + 1 + 2 + 1 = 6, which is the minimum possible total cost.
// Example 2:

// Input: s = "1010", encCost = 3, flatCost = 10

// Output: 12

// Explanation:

// The entire string s = "1010" has length 4 and contains 2 sensitive elements, giving a cost of 4 * 2 * 3 = 24.
// Since the length is even, it can be split into two segments "10" and "10".
// Each segment has length 2 and contains one sensitive element, so each costs 2 * 1 * 3 = 6, giving a total of 12, which is the minimum possible total cost.
// Example 3:

// Input: s = "00", encCost = 1, flatCost = 2

// Output: 2

// Explanation:

// The string s = "00" has length 2 and contains no sensitive elements, so storing it as a single segment costs flatCost = 2, which is the minimum possible total cost.

 

// Constraints:

// 1 <= s.length <= 105
// s consists only of '0' and '1'.
// 1 <= encCost, flatCost <= 105

//not hard. recursive
#define ll long long

class Solution {
public:

    ll splitInto2(int n, int flatCost, int encCost, vector<int>& ps, int start, int end, ll min_cost){
        //find the cost
        ll cost=0;
        
        // for(int i=0;i<n;i++){
        //     cout<<ps[i]<<" ";
        // }
        // cout<<endl;
        int x=ps[end+1]-ps[start];//st.query(start, end);
        // cout<<"x:"<<x<<endl;
        if(x==0){
            cost=flatCost;
            // cout<<"flatCost:"<<flatCost<<endl;
        }
        else{
            cost=(ll)n*x*encCost;
            // cout<<"n*x*encCost:"<<cost<<endl;
        }

        min_cost=min(min_cost, cost);
        // cout<<"min_cost:"<<min_cost<<endl;
        //split into 2 if possible
        if((end-start+1)%2==0){ //can split
            ll cost1=splitInto2(n/2, flatCost, encCost, ps, start, (start+end)/2, min_cost);
            // cout<<"cost1:"<<cost1<<endl;
            ll cost2=splitInto2(n/2, flatCost, encCost, ps, (start+end)/2+1, end, min_cost);
            // cout<<"cost2:"<<cost2<<endl;
            min_cost=min(min_cost, cost1+cost2);
            // cout<<"min_cost:"<<min_cost<<endl;
        }
        return min_cost;
    }
    long long minCost(string s, int encCost, int flatCost) {
        int n=s.size();

        vector<int> v;
        vector<int> ps(n+1,0);
        int i=0;
        for (char c : s) {
            v.push_back(c - '0'); // convert char to int
            ps[i+1]=ps[i]+v[i];
            i++;
        }

        // SegmentTree_Sum st;
        // st.init(n);
        // st.build(v);

        ll min_cost=LLONG_MAX;
        ll cost=splitInto2(n, flatCost, encCost, ps, 0, n-1, min_cost);


        return cost;
    }
};