// Boredom


// Alex doesn't like boredom. That's why whenever he gets bored, he comes up with games. One long winter evening he came up with a game and decided to play it.

// Given a sequence a consisting of n integers. The player can make several steps. In a single step he can choose an element of the sequence (let's denote it ak) and delete it, at that all elements equal to ak + 1 and ak - 1 also must be deleted from the sequence. That step brings ak points to the player.

// Alex is a perfectionist, so he decided to get as many points as possible. Help him.

// Return maximum number of points Alex can earn.

// Constraints:

// 1 <= n <= 10^5

// 1<= ai <= 10^5

// Example:

// Input: n = 9,  a = {1, 2, 1, 3, 2, 2, 2, 2, 3}
 
// Output: 10
 
// Explanation: At first step we need to choose any element equal to 2. After that step our sequence looks like this [2, 2, 2, 2]. Then we do 4 steps, on each step we choose any element equals to 2. In total we earn 10 points.
//codeforces 455A

#include<bits/stdc++.h>
using namespace std;

//dp[i]: max score if considering only number <=i
//recurrence: dp[i]=max(dp[i-1], //skip i
//                        dp[i-2]+value[i]) //consider i
//formulation never considers the fact of choosing ak ignore ak+1.
long long solve(int n, vector<int> a){

    int max_vle=*max_element(a.begin(), a.end());
    
    vector<long long> freq(max_vle+1, 0LL);
    for(int i=0;i<n;i++){
        freq[a[i]]++;
    }
    for(int i=1;i<=max_vle;i++){
        freq[i]*=i;
    }
    
    vector<long long> dp(max_vle+1,0LL);
    dp[1]=freq[1];
    for(int i=2;i<=max_vle;i++){
        dp[i]=max(dp[i-1], dp[i-2]+freq[i]);
    }
    return dp[max_vle];
}

int main(){
    int n;
    cin>>n;
    vector<int> a(n,0);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    long long ans=solve(n, a);

    cout<<ans<<endl;
}