// Remainders Game
// Today Pari and Arya are playing a game called Remainders.

// Pari chooses two positive integer x and k, and tells Arya k but not x. Arya have to find the value . There are n ancient numbers c1, c2, ..., cn and Pari has to tell Arya  if Arya wants. Given k and the ancient values, tell us if Arya has a winning strategy independent of value of x or not. Formally, is it true that Arya can understand the value  for any positive integer x?

// Note, that  means the remainder of x after dividing it by y.

// Return "Yes" if Arya has a winning strategy independent of value x otherwise "No" without quotes.

// Constraints:

// 1 <= n, k <= 10^5

// 1 <= ci <= 10^5

// Example 1:

// Input: n= 4, k= 5, c= [2, 3, 5, 12]
 
// Output: Yes
 
// Explanation: 
// Arya can understand  because 5 is one of the ancient numbers.
// Example 2:

// Input: n= 2, k= 7, c= [2, 3]
 
// Output: No
 
// Explanation: 
// Arya can't be sure what xmod7 is. For example 1 and 7 have the same remainders after dividing by 2 and 3, but they differ in remainders    after dividing by 7.

// https://codeforces.com/problemset/problem/687/b

// know x mod ci uniquely determines x mod lcm(c1, c2, ..., cn)
// if k | lcm(c1, ...., cn), know x mod k
// implementation details
// cannot find lcm directly due to overflow
// prime factorize k
// check all prime factor of k is contained inside any ci
// further optimization
// - remove duplicate in ci by using sort vector (not better) 233ms -> 327ms
// - remove duplicate in ci by using set(not better) 233ms -> 421ms
// - reduce value of ci by gcd with k (not better) 233ms -> 359ms
#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// O(Sqrt(N))
void factoriseOpt(int n, vector<int>& prime, vector<int>& pwr){

    for(int i=2; i*i<=n; i++){
        if(n%i == 0){
            prime.push_back(i);
            int cnt = 0;
            while(n%i == 0){
                cnt++;
                n = n/i;
            }
            pwr.push_back(cnt);

            //cout<<i<<"^"<<cnt<<",";
        }
    }

    //Out of the loop
    if(n!=1){
        prime.push_back(n);
        pwr.push_back(1);
        //cout << n <<"^"<< 1 <<endl;
    }
}


string solve(int n, int k, vector<int> c){
    vector<int> prime;
    vector<int> pwr;

    factoriseOpt(k, prime, pwr);

    // this adds more runtime----------------
    // for (int i = 0; i < n; i++) {
    //     c[i] = gcd(c[i], k);   // shrink c[i] to only useful factors
    // }
    // this adds more runtime----------------

    // cerr<<k<<endl;
    // for(int i=0;i<prime.size();i++){
    //     cerr<<prime[i]<<" "<<pwr[i]<<endl;
    // }
    // cerr<<endl;

    // this adds more runtime----------------
    // set<int> s(c.begin(), c.end()); //remove duplicates
    // this adds more runtime----------------
    
    // this adds more runtime----------------
    // Remove duplicates
    // sort(c.begin(), c.end());
    // c.erase(unique(c.begin(), c.end()), c.end());
    // this adds more runtime----------------

    bool k_divide_lcm=true;
    for(int i=0;i<prime.size();i++){
        // int prime_max_pow=1;

        //this causes TLE-----------------
        // for(int j=0;j<pwr[i];j++){
        //     prime_max_pow*=prime[i];
        // }
        //this causes TLE-----------------

        bool find_c=false;
        for(int s_: c){
            // if(c[j]%prime_max_pow==0){
            //     find_c=true;
            //     break;
            // }

            int cnt = 0, temp = s_;
            while(temp % prime[i] == 0){
                temp /= prime[i];
                cnt++;
            }
            if(cnt >= pwr[i]){
                find_c = true;
                break;
            }
        }

        
        if(!find_c){
            k_divide_lcm=false;
            break;
        }
    }

    if(k_divide_lcm){
        return "Yes";
    }
    else{
        return "No";
    }
}

int main(){
    int n, k;

    //these 2 lines resolve TLE
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //these 2 lines resolve TLE

#ifndef ONLINE_JUDGE
	freopen("input.txt",  "r",  stdin);
	freopen("output.txt", "w", stdout);
#endif
    cin>>n>>k;
    vector<int> c(n,0);
    for(int i=0;i<n;i++){
        cin>>c[i];
    }

    string ans = solve(n, k, c);
    cout<<ans<<endl;
}
