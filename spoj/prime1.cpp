// https://www.spoj.com/problems/PRIME1/

#include<iostream>
#include<vector>
#include <cstring> //for memset
using namespace std;

#define N 100000




//Sieve of Eratosthenes (O(NLogLogN))
vector<int> sieve(){
    bool sieveArr[N+1];
    vector<int> primes;
    memset(sieveArr, false, N);

	for(long long i=2; i<=N; i++){
		//mark non primes as 1
		if(!sieveArr[i]){
			primes.push_back(i);
			//marking all multiples of i (prime) as non-prime
			for(long long j= i*i; j<=N; j+=i){
				sieveArr[j] = true; //non-prime
			}
		}
	}

    return primes;
}

// Segmented Sieve

int main(){

	//Precompute
	vector<int> primes = sieve();
	int t;
	cin>>t;

	while(t--){
		int n,m;
		cin>>m >> n;

		vector<bool> segment(n-m+1,false);
		

		//iterate over the primes, mark multiples of 
		// prime in segment array as non-prime (1)

		for(auto p : primes){

			//stop the loop if prime is larger than root n
			if( p*p > n){
				break;
			}

			int start = (m/p) * p;
			
			// don't start from 0, instead 2 * prime. else wrong ans as it will label p as non-prime.
			if(p>=m and p<=n){
				start = 2 * p;
			}

			for(int j = start; j<=n; j = j + p){
				if(j < m){
					continue;
				}
				//non-prime
				segment[j - m] = true;
			}
		}
					//Loop over the number m ... n and print the primes
		for(int i=m; i<=n; i++){
			if(!segment[i-m] and i!=1){
				cout<<i<<endl;
			}
		}
		cout<<endl;

	}

	return 0;
}


