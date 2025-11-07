// Math
// Given an integer n, you can perform the following operations zero or more times:

// mul x: multiplies n by x (where x is an arbitrary positive integer).

// sqrt: replaces n with √n (to apply this operation, √n must be an integer).

// You can perform these operations as many times as you like. What is the minimum value of n, that can be achieved, and what is the minimum number of operations, to achieve that minimum value?

// Return an array containing the minimum value of n and the number of operations required to achieve that value respectively.

// Constraints:

// 1 <= n <= 10^6

// Example:

// Input: n= 5184
 
// Output: {6, 4}
 
// Explanation: You can first apply sqrt to get 72, then mul 18 to get 1296 and finally two more sqrt and you get 6.

#include<bits/stdc++.h>
using namespace std;


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

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int msbPos(unsigned int n) {
    if (n == 0) return -1;  // No MSB for 0
    return 31 - __builtin_clz(n);
}

vector<int> solve(int n){
    vector<int> prime;
    vector<int> pwr;
    factoriseOpt(n, prime, pwr);
    
    int ret1=1;
    for(int i=0;i<prime.size();i++){
        ret1*=prime[i];
    }
    
    //all pwr must be same and power of 2.
    sort(pwr.begin(), pwr.end());
    
    int ret2=0;
    if(isPowerOfTwo(pwr.back())){
        ret2=msbPos(pwr.back());
        if(pwr.front()!=pwr.back()){
            ret2+=1;
        }
    }
    else{
        ret2=msbPos(pwr.back())+1;
        if(pwr.front()!=pwr.back()){
            ret2+=1;
        }
    }
    vector<int> ret_list;
    ret_list.push_back(ret1);
    ret_list.push_back(ret2);
    return ret_list;
}