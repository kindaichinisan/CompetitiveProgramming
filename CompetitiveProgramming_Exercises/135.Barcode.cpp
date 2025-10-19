// Barcode


// You've got an n × m pixel picture. Each pixel can be white or black, Character "." represents a white pixel and "#" represents a black pixel. The picture description doesn't have any other characters besides "." and "#". Your task is to change the colors of as few pixels as possible to obtain a barcode picture.

// A picture is a barcode if the following conditions are fulfilled:

// All pixels in each column are of the same color.

// The width of each monochrome vertical line is at least x and at most y pixels. In other words, if we group all neighboring columns of the pixels with equal color, the size of each group can not be less than x or greater than y.

// Return minimum number of pixels to repaint.

// Constraints:

// 1 <= n,m,x,y <= 1000

// x <= y

// Example:

// Input: n= 6, m= 5, x= 1, y= 2, 
//        grid=  ##.#.
//               .###.
//               ###..
//               #...#
//               .##.#
//               ###..
// Output: 11
 
// Explanation:
// In the test sample the picture after changing some colors can looks as follows:
 
// .##..
// .##..
// .##..
// .##..
// .##..
// .##..
//codeforces 225C
#include<bits/stdc++.h>
using namespace std;

//int dp[colidx+1][color]: min pixel to color, considering first colidx col, last pattern being color. color=0 (W)
//dp[colidx][B]=dp[prev_pat_colidx][W]+num_pix to color last col to black

int solve(int n, int m,int x, int y, vector<vector<char>> grid){
    
    // cout<<n<<" "<<m<<" "<<x<<" "<<y<<endl;
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<grid[i][j];
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    
    vector<int> num_white_prefixsum(m+1,0); //1-idx
    for(int j=0;j<m;j++){
        num_white_prefixsum[j+1]=num_white_prefixsum[j];
        for(int i=0;i<n;i++){
            if(grid[i][j]=='.'){
                num_white_prefixsum[j+1]++;
            }
        }
    }
    
    vector<vector<int>> dp(m+1, vector<int>(2, 1000000000)); //1-idx
    dp[0][0]=0; //b4 first col, nothing to color
    dp[0][1]=0;
    
    for(int j=0;j<m;j++){
        //cout<<"j: "<<j<<endl;
        for(int k=x; k<=y;k++){
            int prev_col=j+1-k; //0-idx
            //cout<<"prev_col: "<<prev_col<<endl;
            if(prev_col>=0){
                
                int num_whites=num_white_prefixsum[j+1]-num_white_prefixsum[prev_col];
                int num_blacks=n*k-num_whites;
                //W. to colour white
                dp[j+1][0]=min(dp[j+1][0], dp[prev_col][1]+num_blacks);
                
                //B.
                dp[j+1][1]=min(dp[j+1][1], dp[prev_col][0]+num_whites);
                
                //cout<<dp[j+1][0]<<" "<<dp[j+1][1]<<endl;
            }
        }
    }
    
    // for(int j=0;j<=m;j++){
    //     cout<<dp[j][0]<<" ";
    // }
    // cout<<endl;
    // for(int j=0;j<=m;j++){
    //     cout<<dp[j][1]<<" ";
    // }
    // cout<<endl;
    
    return min(dp[m][0], dp[m][1]);
}

int main(){
    int n, m, x, y;

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin>>n>>m>>x>>y;

    // cout<<n<<" "<<m<<" "<<x<<" "<<y<<endl;

    vector<vector<char>> grid(n, vector<char>(m,' '));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>grid[i][j];
        }
    }

    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout<<grid[i][j];
    //     }
    //     cout<<endl;
    // }

    int ans = solve(n, m, x, y, grid);
    cout<<ans<<endl;
}