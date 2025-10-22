// Maximum Number of Events That Can Be Attended


// You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. You are also given an integer k which represents the maximum number of events you can attend.

// You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.

// Return the maximum sum of values that you can receive by attending events.

// Constraints:

// 1 <= k <= events.length

// 1 <= k * events.length <= 10^6

// 1 <= startDayi <= endDayi <= 10^9

// 1 <= valuei <= 10^6

// Example :



// Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2 
 
// Output: 7
 
// Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
//leetcode 1751

//dp[i][k]: considering the first ith evts using up to k (including k) event
//my soln is O(N^2*k) will TLE
//my soln TLE because I use O(N) to search for vle. 
//If I use upper_bound, I will use O(lgN) to search for vle.
//upper_bound requires sorted array.
class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n=events.size();
    
        //k=2;
        
        cout<<k<<endl;
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];  // sort by the 2nd element (index 1)
        });
        
        // for(int i=0;i<n;i++){
        //     cout<<events[i][0]<<" "<<events[i][1]<<" "<<events[i][2]<<endl;
        // }
        
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        
        int maxi=0;
        for(int i=0;i<n;i++){ //O(N)
            dp[i+1][1]=events[i][2]; //ith evt 1st event confirm can work.
            maxi=max(maxi,dp[i+1][1]);
            for(int j=1;j<=k;j++){ //O(k)
                for(int a=0;a<i;a++){ //O(N)
                    //cout<<"i "<<i<<" a "<<a<<" "<<events[a][1]<<" "<<events[i][0]<<endl;
                    if(events[a][1]<events[i][0]){ //event a end day b4 event i start day
                        dp[i+1][j]=max(dp[i+1][j], events[i][2]+dp[a+1][j-1]);
                        maxi=max(maxi,dp[i+1][j]);
                    }
                }
            }
        }
        
        // for(int i=0;i<n+1;i++){
        //     for(int j=0;j<2;j++){
        //         cout<<dp[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        
        return maxi;
    }
};

//use upper_bound to search
//using upper_bound may not get the max vle.
//change formulation abit
class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        int n=events.size();
    
        cout<<k<<endl;
        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];  // sort by the 2nd element (index 1)
        });
        
        vector<int> endtime_list;
        for(int i=0;i<n;i++){
            endtime_list.push_back(events[i][1]);
        }
        // for(int i=0;i<n;i++){
        //     cout<<events[i][0]<<" "<<events[i][1]<<" "<<events[i][2]<<endl;
        // }
        
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        
        int maxi=0;
        for(int i=0;i<n;i++){ //O(N)
            dp[i+1][1]=events[i][2]; //ith evt 1st event confirm can work.
            maxi=max(maxi,dp[i+1][1]);
            for(int j=1;j<=k;j++){ //O(k)
                //find the last endtime that start earlier than cur start time
                auto ite=lower_bound(endtime_list.begin(), endtime_list.end(), events[i][0]);
                int idx=ite-endtime_list.begin()-1;
                
                dp[i+1][j]=max(dp[i][j], events[i][2]+dp[idx+1][j-1]);
                maxi=max(maxi,dp[i+1][j]);
                
            }
        }
        
        // for(int i=0;i<n+1;i++){
        //     for(int j=0;j<k;j++){
        //         cout<<dp[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        
        return maxi;
    }
};

//Better soln is O(N*logN*k)
class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        // Sort events by end day
        sort(events.begin(), events.end(), [](auto& a, auto& b) {
            return a[1] < b[1];
        });

        int n = events.size();
        vector<int> endTimes(n);
        for (int i = 0; i < n; ++i)
            endTimes[i] = events[i][1];

        // dp[k] means max value using up to k events
        vector<int> dp(n + 1, 0), prev_dp(n + 1, 0);

        for (int t = 1; t <= k; ++t) {
            for (int i = 1; i <= n; ++i) {
                // Find the last non-overlapping event using binary search
                // find last endtime that ends earlier than cur start time. 
                int idx = upper_bound(endTimes.begin(), endTimes.end(), events[i - 1][0] - 1) - endTimes.begin();

                // Either skip current event or take it
                dp[i] = max(dp[i - 1], prev_dp[idx] + events[i - 1][2]);
            }
            prev_dp.swap(dp);
        }

        return prev_dp[n];
    }
};