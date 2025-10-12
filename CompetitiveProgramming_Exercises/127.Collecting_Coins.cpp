// Collecting Coins


// You are given a two-dimensional integer matrix where each cell represents number of coins in that cell. Assuming we start at matrix[0][0], and can only move right or down, find the maximum number of coins you can collect by the bottom right corner.

// Constraints

// n, m ≤ 100 where n and m are the number of rows and columns in matrix.

// Example:

// Input

// matrix = [
//     [0, 3, 1, 1],
//     [2, 0, 0, 4]
// ]
// Output

// 9
// Explanation

// We take the following path: [0, 3, 1, 1, 4]

#include<bits/stdc++.h>
using namespace std;

int solve(vector<vector<int>> matrix) {
    int rows=matrix.size();
    int cols=matrix[0].size();
    vector<vector<long long>> res(rows, vector<long long>(cols,0));
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(i==0){
                if(j==0){
                    res[i][j]=matrix[i][j];
                }
                else{
                    res[i][j]=res[i][j-1]+matrix[i][j];
                }
            }
            else{
                if(j==0){
                    res[i][j]=res[i-1][j]+matrix[i][j];
                }
                else{
                    res[i][j]=max(res[i-1][j],res[i][j-1])+matrix[i][j];
                }
            }
        }
    }
    return (int)res[rows-1][cols-1];
}