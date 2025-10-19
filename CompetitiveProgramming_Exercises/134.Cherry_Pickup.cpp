// Cherry Pickup


// Given a rows x cols matrix grid representing a field of cherries. Each cell in grid represents the number of cherries that you can collect.

// You have two robots that can collect cherries for you, Robot #1 is located at the top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) of the grid.

// Return the maximum number of cherries collection using both robots by following the rules below:

// From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).

// When any robot is passing through a cell, It picks it up all cherries, and the cell becomes an empty cell (0).

// When both robots stay on the same cell, only one of them takes the cherries.

// Both robots cannot move outside of the grid at any moment.

// Both robots should reach the bottom row in the grid.

// Constraints:

// rows == grid.length

// cols == grid[i].length

// 2 <= rows, cols <= 70

// 0 <= grid[i][j] <= 100


// Example:



// Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
 
// Output: 28
 
// Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
// Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
// Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
// Total of cherries: 17 + 11 = 28.
//leetcode 1463

#include<bits/stdc++.h>
using namespace std;

//dp[i][j][k]: max number of cherry collected by robot 1 when reach (i,j) and collected by robot 2 when reach (i,k)
//robot1 can be from (i-1,j-1),(i-1,j),(i-1,j+1), robot2 can be from (i-1,k-1),(i-1,k),(i-1,k+1).
//dp[i][j][k]=grid[i][j]+max(dp[i-1][j-1][k-1], dp[i-1][j-1][k], dp[i-1][j-1][k+1],
//        dp[i-1][j][k-1], dp[i-1][j][k], dp[i-1][j][k+1],
//        dp[i-1][j+1][k-1], dp[i-1][j+1][k], dp[i-1][j+1][k+1])
int cherryPickup(vector<vector<int>> grid) {
    int rows=grid.size();
    int cols=grid[0].size();
    
    vector<vector<vector<int>>> dp(rows, vector<vector<int>>(cols,vector<int>(cols, 0)));
    
    
    dp[0][0][cols-1]=grid[0][0]+grid[0][cols-1]; //robot1 at (0,0) and robot2 at (0,cols-1)

    for(int i=1;i<rows;i++){
        for(int j=0;j<cols;j++){
            for(int k=cols-1; k>=0;k--){
                //consider robot1
                int maxi=INT_MIN;
                for(int a=-1;a<=1;a++){
                    for(int b=-1;b<=1;b++){
                        int c=j+a; //robot1 prev row col
                        int d=k+b; //robot2 prev row col
                        if(c>=0 && c<=cols-1 && c<=(i-1) && d>=0 && d<=cols-1 && d>=cols-1-(i-1)){ //inside grid and robot1 moves from top left
                            if(dp[i-1][c][d]>maxi){
                                maxi=max(maxi,dp[i-1][c][d]);
                            }
                        }
                    }
                    
                }
                dp[i][j][k]=grid[i][j]+maxi;
                
                if(j!=k){
                    dp[i][j][k]+=grid[i][k];
                }
            }
        }
    }
    
    int ret=INT_MIN;
    for(int j=0;j<cols;j++){
        for(int k=0;k<cols;k++){
            if(ret<dp[rows-1][j][k]){
                ret=dp[rows-1][j][k];
            }
        }
    }
    return ret; 
}