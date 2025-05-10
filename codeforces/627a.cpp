#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a, b;
	cin >> a >> b;
	long long diff = a - b;
	if (diff&1 || (diff >> 1)&b) cout << 0 << endl;
	else {
		int delta = 0;
		if (diff <= 1) delta = -2;
		cout << (1ll<<__builtin_popcountll(b)) + delta << endl;
	}
	return 0;
}