#include<bits/stdc++.h>
using namespace std;

string K;
int D;
long long memo[10000][2][100];
const int mod = 1e9 + 7;

int dp(int i, bool last, int modulo){

    // cout<<i<<" "<<last<<" "<<mod<<endl;
    if(i==K.size()){
        return modulo==0?1:0;
    }
    
    //cout<<i<<" "<<last<<" "<<mod<<endl;
    long long& ans=memo[i][last][modulo];
    if(ans!=-1) return (int)ans;

    // cout<<i<<" "<<last<<" "<<mod<<endl;

    ans=0LL;
    // cout<<"K[i]"<<K[i]<<endl;
    int till = last? K[i]-'0': 9;
    // cout<<"till"<<till<<endl;

    for(int digit=0;digit<=till;digit++){
        // cout<<i+1<<endl;
        // cout<<(last&&(i==till))<<endl;
        // cout<<mod<<" "<<i<<" "<<D<<endl;
        // cout<<((mod+i)%D)<<endl;
        // cout<<"digit"<<digit<<endl;
        ans+=dp(i+1, last&&(digit==till), (modulo+digit)%D);
        // cout<<"digit"<<digit<<endl;
    }
    // cout<<"ans: "<<ans<<endl;
    ans%=mod;

    return (int)ans;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin>>K>>D;
    // cout<<K<<endl<<D<<endl;

    memset(memo, -1, sizeof(memo));

    // for(int i=0;i<3;i++){
    //     for(int j=0;j<2;j++){
    //         for(int k=0;k<4;k++){
    //             cout<<memo[i][j][k]<<" ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }

    cout<<(dp(0, true, 0)-1+mod)%mod<<endl;

    return 0;
}