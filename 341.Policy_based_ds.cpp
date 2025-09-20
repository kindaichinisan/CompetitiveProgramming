#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update>
        new_data_set;

int main() {
	new_data_set St;
	St.insert(1);

	for (int i = 0; i < St.size(); i++) {
		cout << i << " -> " << *St.find_by_order(i) << '\n';
	}

	for (int i = 0; i < 15; i++) {
		cout << i << " -> " << St.order_of_key(i) << '\n';
	}

}