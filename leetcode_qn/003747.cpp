// 3747. Count Distinct Integers After Removing Zeros

// You are given a positive integer n.

// For every integer x from 1 to n, we write down the integer obtained by removing all zeros from the decimal representation of x.

// Return an integer denoting the number of distinct integers written down.

 

// Example 1:

// Input: n = 10

// Output: 9

// Explanation:

// The integers we wrote down are 1, 2, 3, 4, 5, 6, 7, 8, 9, 1. There are 9 distinct integers (1, 2, 3, 4, 5, 6, 7, 8, 9).

// Example 2:

// Input: n = 3

// Output: 3

// Explanation:

// The integers we wrote down are 1, 2, 3. There are 3 distinct integers (1, 2, 3).

 

// Constraints:

// 1 <= n <= 1015

//beats 13.79%
#define ll long long
class Solution {
public:

    vector<int> convertToVector(ll num){

        //num=100;
        vector<int> ret;
        while(num){
            ret.push_back(num%10);
            num/=10;
        }
        return ret;
    }
    
    //key insights is power of 10=sum(9^i)
    //1=9^0
    //10=9^1
    //100=9^2+9^1
    //1000=9^3+9^2+9^1
    //200=(9^2+9^1)+
    //2300=2*(9^3+9^2+9^1)+3*(9^2+9^1)
    long long countDistinct(long long n) {
        
        vector<int> arr=convertToVector(n);
        
        ll ret=0;

        ll powerofnine=1LL;

        //count the number up to the number of digit-1.
        //if 145, count from 1 to 99.
        for(int i=0;i<arr.size()-1;i++){
            powerofnine*=9;
            ret+=powerofnine;
        }
        cout<<ret<<endl;
        
        for(int i=arr.size()-1;i>=0;i--){
            if(arr[i]==0)
                break;
            if(i==0){
                ret+=arr[i];
            }
            else{
                ret+=(arr[i]-1)*powerofnine;
            }
            powerofnine/=9;
        }
        return ret;
    }
};

//use string instead of vector<int> beats 100%. No is becos of cout. W/o cout. both beats 100%
//key insights is power of 10=sum(9^i)
//1=9^0
//10=9^1
//100=9^2+9^1
//1000=9^3+9^2+9^1
//200=(9^2+9^1)+
//2300=2*(9^3+9^2+9^1)+3*(9^2+9^1)
long long countDistinct(long long n) {
    
    string arr=std::to_string(n);
    
    ll ret=0;

    ll powerofnine=1LL;

    //count the number up to the number of digit-1.
    //if 145, count from 1 to 99.
    for(int i=0;i<arr.size()-1;i++){
        powerofnine*=9;
        ret+=powerofnine;
    }
    cout<<ret<<endl;
    
    // for(int i=arr.size()-1;i>=0;i--){
    for(int i=0;i<arr.size();i++){
        if(arr[i]=='0')
            break;
        if(i==arr.size()-1){
            ret+=arr[i]-'0';
        }
        else{
            ret+=(arr[i]-'0'-1)*powerofnine;
        }
        powerofnine/=9;
    }
    return ret;
}