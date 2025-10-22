#include<bits/stdc++.h>
using namespace std;

#define mod 1000000007

//int dp[idx][s]: number of way to fill idx-th number with s smaller number.
//top down (recursive) approach
//O(N^3): to fill up dp[N][N] needs N^2. Each fill up require O(N). Hence O(N^3)
int dpFn(const string& str, vector<vector<int>>& dp, int N, int idx, int s){

    //cout<<"dpFn "<<idx<<" "<<s<<endl;
    if(idx==N){ //reach the end. is a valid number.
        return 1;
    }

    int& ans=dp[idx][s];

    if(ans!=-1){
        return ans;
    }

    ans=0;

    if(str[idx-1]=='<'){
        
        int b=N-idx-s;
        for(int i=0;i<b;i++){ //use the big number
            ans+=dpFn(str, dp, N, idx+1, s+i); //dp[idx][s]=dp[idx+1][s]+...+dp[idx+1][s+b-1]
            ans%=mod;
        }
    }
    else{
        for(int i=0;i<s;i++){ //use the small number
            ans+=dpFn(str, dp, N, idx+1, i); //dp[idx][s]=dp[idx+1][0]+...+dp[idx+1][s-1]
            ans%=mod;
        }

    }
    
    return ans;
}


//int dp[idx][s]: number of way to fill idx-th number with s smaller number.
//bottom up (iterative) approach
//O(N^2): to fill up dp[N][N] needs N^2. Each fill up require O(1). Hence O(N^2)
//need to use long long for qn which requires modulo for intermediate sum > INT_MAX
int dpFn2(const string& str, int N){

    vector<vector<long long>> dp(N+1, vector<long long>(N,0));
    dp[N][0] = 1LL;

    // cout<<"dp ini"<<endl;
    // for(int i=0;i<=N;i++){
    //     for(int j=0;j<N;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    for(int idx=N-1;idx>0;idx--){

        //prefixsum that is 0-idx
        //dp[][0]=dp[][0]
        //dp[][1]=dp[][1]+dp[][0]
        for(int s=0;s<N-1;s++){
            dp[idx+1][s+1]+=dp[idx+1][s];
        }

        // cout<<"dp prefixsum"<<endl;
        // for(int i=0;i<=N;i++){
        //     for(int j=0;j<N;j++){
        //         cout<<dp[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }

        for(int s=0;s<N;s++){ //s can be 0 to N-1
            if(str[idx-1]=='<'){
                int b=N-idx-s; //b can be N-idx to 1-idx
                if(b>=0){
                    if(s==0){
                        dp[idx][s]=dp[idx+1][s+b-1];
                    }
                    else{
                        dp[idx][s]=dp[idx+1][s+b-1]-dp[idx+1][s-1];
                    }
                }
                dp[idx][s]=(dp[idx][s]%mod+mod)%mod;

                // cout<<"dp<"<<s<<" "<<b<<" "<<N-idx<<endl;
                // for(int i=0;i<=N;i++){
                //     for(int j=0;j<N;j++){
                //         cout<<dp[i][j]<<" ";
                //     }
                //     cout<<endl;
                // }
            }
            else{
                if(s>0){
                    dp[idx][s]=dp[idx+1][s-1];
                    dp[idx][s]%=mod;
                }

                // cout<<"dp>"<<s<<endl;
                // for(int i=0;i<=N;i++){
                //     for(int j=0;j<N;j++){
                //         cout<<dp[i][j]<<" ";
                //     }
                //     cout<<endl;
                // }
            }
        }
    }

    // cout<<"dp final"<<endl;
    // for(int i=0;i<=N;i++){
    //     //cout<<N<<endl;
    //     for(int j=0;j<N;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    long long ans=0LL;
    for(int s=0;s<N;s++){
        //cout<<dp[1][s]<<endl;
        ans+=dp[1][s];
    }
    ans%=mod;
    return (int)ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int N;
    string s;

    cin>>N>>s;

    //cout<<N<<" "<<s<<endl;

    // vector<vector<int>> dp(N, vector<int>(N,-1));
    // int ans=0;
    // for(int i=0;i<N;i++){
    //     ans+=dpFn(s, dp, N, 1, i);
    //     ans%=mod;
    // }

    // for(int i=0;i<N;i++){
    //     for(int j=0;j<N;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    int ans=dpFn2(s, N);

    cout<<ans<<endl;
    
    return 0;


}