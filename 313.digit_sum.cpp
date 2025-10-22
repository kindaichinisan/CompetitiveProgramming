#include<bits/stdc++.h>

#define int long long int
#define F first
#define S second
#define pb push_back

using namespace std;

const int N = 1e4;

string k;
int d, apaar = 1e9 + 7;
int memo[N][2][100];

//print from o=0 up to n-digit. go(0, 0)
//print 2 digits number
//i is the cur iteration of digit (0=one digit, 1=ten digit)
//num is the digit stored from right to left.
int n_digit=1;
void go(int i, int num){
	if(i==n_digit){
		cout<<num<<'\n';
		return;
	}
	for(int digit=0;digit<=9;digit++){
		go(i+1,num*10+digit);
	}
}

//print up to certain number
string s="752";
void go2(int i, bool last, int num){

	if(i == s.size()){
		cout<<num<<'\n';
		return;
	}

	int till=last ? (s[i]-'0') : 9;

	//if last is false, it will never be true for subtree.
	for(int digit=0;digit<=till;digit++){
		go2(i+1, last&&(digit==till), num*10+digit);
	}
}

//i range from 0 to 10^4
//last is true or false
//mod range from 0 to d
//number of states in dp to memo: 2*100*10^4
int dp(int i, bool last, int mod) {
	if (i == k.size()) {
		return (mod == 0);
	}

	int &ans = memo[i][last][mod];
	if (ans != -1) return ans;

	ans = 0;

	int till = last ? (k[i] - '0') : 9;

	for (int digits = 0; digits <= till; digits++) {
		ans += dp(i + 1, last && (digits == till), (mod + digits) % d);
		ans %= apaar;
	}

	return ans;
}

int32_t main() {

	// go(0, 0);
	go2(0, true, 0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	cin >> k >> d;

	memset(memo, -1, sizeof(memo));

	cout << (dp(0, 1, 0) - 1 + apaar) % apaar;

	return 0;
}