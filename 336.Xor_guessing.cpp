#include<bits/stdc++.h>

#define int long long int
#define F first
#define S second
#define pb push_back

using namespace std;

int32_t main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int ans = 0;

	cout << "? ";
	for (int i = 1; i <= 100; i++) {
		cout << i << " ";
	} cout << endl;

	int x;
	cin >> x;

	for (int i = 7; i <= 13; i++) {
		if ((x >> i) & 1) {
			ans |= (1 << i);
		}
	}

	cout << "? ";
	for (int i = 1; i <= 100; i++) {
		cout << (i << 7) << " ";
	} cout << endl;

	cin >> x;

	for (int i = 0; i <= 6; i++) {
		if ((x >> i) & 1) {
			ans |= (1 << i);
		}
	}

	cout << "! " << ans << endl;

	return 0;
}