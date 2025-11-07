class NumberTheory{
    int gcd(int a, int b) {
        while (b) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    int lcm(int a, int b) {
        return a / gcd(a, b) * b; // careful with overflow
    }

    //prime sieve: O(N*lg(lg(N)))
    vector<bool> primeSieve(long long N){

        using ll=long long;

        vector<bool> sieve(N, true);
        //Mark 1 and 0 as not prime
        sieve[1] = sieve[0] = false;

        //start from 3 and mark all multiples of given i (prime) as not prime
        for(ll i=2; i<=N; i++){	
            if(sieve[i]){ //if not marked as non-prime, then is prime
                for(ll j = i*i; j<=N; j = j + i){
                    //marking j as not prime
                    sieve[j] = false;
                }
            }
        }

        return sieve;
    }

    //Brute Force O(N)
    void factorise(int n, vector<int>& prime, vector<int>& pwr){

        for(int i=2; i<=n; i++){
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
    }

    //Optimised Approach
    /*
    Obs: Once N is reduced to a prime number, the 
    only factor that number will be the number itself.

    If a number doesn't have any factor till sqrt(n) 
    then it is a prime number.
    */
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
};