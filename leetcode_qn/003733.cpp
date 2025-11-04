// You are given two integer arrays of size 2: d = [d1, d2] and r = [r1, r2].

// Two delivery drones are tasked with completing a specific number of deliveries. Drone i must complete di deliveries.

// Each delivery takes exactly one hour and only one drone can make a delivery at any given hour.

// Additionally, both drones require recharging at specific intervals during which they cannot make deliveries. Drone i must recharge every ri hours (i.e. at hours that are multiples of ri).

// Return an integer denoting the minimum total time (in hours) required to complete all deliveries.

 

// Example 1:

// Input: d = [3,1], r = [2,3]

// Output: 5

// Explanation:

// The first drone delivers at hours 1, 3, 5 (recharges at hours 2, 4).
// The second drone delivers at hour 2 (recharges at hour 3).
// Example 2:

// Input: d = [1,3], r = [2,2]

// Output: 7

// Explanation:

// The first drone delivers at hour 3 (recharges at hours 2, 4, 6).
// The second drone delivers at hours 1, 5, 7 (recharges at hours 2, 4, 6).
// Example 3:

// Input: d = [2,1], r = [3,4]

// Output: 3

// Explanation:

// The first drone delivers at hours 1, 2 (recharges at hour 3).
// The second drone delivers at hour 3.
 

// Constraints:

// d = [d1, d2]
// 1 <= di <= 109
// r = [r1, r2]
// 2 <= ri <= 3 * 104

//3 cases:
//drone 0 is limiting factor, drone 1 finishes first. Some drone 0 recharge slot not used.
//drone 1 is limiting factor, drone 0 finishes first. Some drone 1 recharge slot not used.
//drone 0 and 1 recharge slots are all used. No wastage. Can be taken to be 1 drone with sum of delivery, and recharge time=lcm(r0, r1)
//not sure why maximum gives the correct case.
//need to minus 1 as all the answer includes the last recharge slot
class Solution {
public:
    
    long long minimumTime(vector<int>& d, vector<int>& r) {
        
        long long drone0_limiting=ceil( (d[0]*1ll*r[0]*1.0) / (r[0]-1) );
        long long drone1_limiting=ceil((d[1]*1ll*r[1]*1.0)/(r[1]-1));
        long long r_lcm=lcm(r[0], r[1]); //has implementation in std lib
        long long drone0_drone1_equal=ceil(((d[0]+0ll+d[1])*r_lcm*1.0)/(r_lcm-1));
        
        // cout<<drone0_limiting<<endl;
        // cout<<drone1_limiting<<endl;
        // cout<<drone0_drone1_equal<<endl;
        long long ret=max({drone0_limiting, drone1_limiting, drone0_drone1_equal});

        ret=ret-1;

        return ret;
    }
};

//good soln O(1)
// https://leetcode.com/problems/minimum-time-to-complete-all-deliveries/solutions/7320879/beats-100-o1-complexity-very-detailed-ea-hxtz/
//binary search O(lg N)
