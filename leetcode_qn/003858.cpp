// 3858. Minimum Bitwise OR From Grid

// You are given a 2D integer array grid of size m x n.

// You must select exactly one integer from each row of the grid.

// Return an integer denoting the minimum possible bitwise OR of the selected integers from each row.

 

// Example 1:

// Input: grid = [[1,5],[2,4]]

// Output: 3

// Explanation:

// Choose 1 from the first row and 2 from the second row.
// The bitwise OR of 1 | 2 = 3​​​​​​​, which is the minimum possible.
// Example 2:

// Input: grid = [[3,5],[6,4]]

// Output: 5

// Explanation:

// Choose 5 from the first row and 4 from the second row.
// The bitwise OR of 5 | 4 = 5​​​​​​​, which is the minimum possible.
// Example 3:

// Input: grid = [[7,9,8]]

// Output: 7

// Explanation:

// Choosing 7 gives the minimum bitwise OR.
 

// Constraints:

// 1 <= m == grid.length <= 105
// 1 <= n == grid[i].length <= 105
// m * n <= 105
// 1 <= grid[i][j] <= 105


// greedy. Check th Most Significant bit.
// use forbidden to check for bit that cannot be 1.
// use ans to store partial answer after considering the first n bit.
class Solution {
public:
    int minimumOR(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();

        //consider each bit from left to right
        int ans=0;
        int forbidden=0; //bit is 1 implies that bit for ans shld be 0.
        for(int i=31;i>=0;i--){

            int testForbidden = forbidden | 1<<i;
            bool allrowsatisfied=true;
            for(int j=0;j<m;j++){ //for each row
                bool found=false;
                for(int k=0;k<n;k++){
                    if((grid[j][k] & testForbidden)==0){ //found a col inside row that satisfy current testForbidden, go to next row
                        found=true;
                        break;
                    }
                }
                if(!found){ //if did not find a col inside row that satisfy current testForbidden, no need check other row
                    allrowsatisfied=false;
                    break;
                }
            }

            if(allrowsatisfied){
                forbidden = testForbidden;
            }
            else{
                ans += (1<<i);

            }
        }

        return ans;
    }
};