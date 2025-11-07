// Alice and Candies


// Alice loves candies, so she went into a candy shop. Now the shopkeeper sells candies in packets and all packets contain an odd number of candies (1, 3, 5, 7.....). Alice wants exactly n candies but she also loves patterns so she decided to buy candies only if the number of candies in the packets is consecutive and distinct (means she cannot buy the same candy packet more than once) and the sum of all the candies in those packets is exactly n.

// Alice has an infinite amount of money and the shopkeeper also has an infinite amount of candy packets, so Alice wonders how many different sets of candy packets she can buy.

// Find the number of different sets of candy packets that Alice can buy.

// Constraints:

// 1 <= n <= 10^9

// Example:

// Input: edges = 45
 
// Output: 3
 
// Explanation:  
// Alice can buy 3 set of candy packets.
 
// 1. {5,7,9,11,13}
 
// 2. {13,15,17}
 
// 3. {45}

// https://www.hackerearth.com/practice/math/number-theory/basic-number-theory-1/practice-problems/algorithm/lola-and-candies-36b57b1b/

#include <iostream>
#include <vector>
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

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt",  "r",  stdin);
    freopen("output.txt", "w", stdout);
#endif
	int num;
	cin >> num;    //Reading input from STDIN
    //cout<<num<<endl;

    int ret=1;
    bool done=false;
    if(num!=1)
    {
        if(num%2==0){ //even number must be multiple of 4
            if(num%4==0){
                num/=4;
            }
            else{ //not possible if even number is not multiple of 4
                ret=0;
                done=true;
            }
        }

        if(!done){
            vector<int> prime;
            vector<int> pwr;
            factoriseOpt(num, prime, pwr);
            //cout<<prime.size()<<" "<<pwr.size()<<endl;

            for(int i=0;i<pwr.size();i++){
                ret*=pwr[i]+1;
            }

            ret=(ret+1)/2;
        }
    }
    
	cout << ret << endl;	// Writing output to STDOUT
}