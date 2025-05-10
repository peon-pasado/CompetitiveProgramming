#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; ++tc) {
		int n, m;
		cin >> n >> m;
		cout << "Case " << tc << ": ";
		if (n == 0 && m == 0) cout << 1 << endl;
		else {
			int g = __gcd(n, m);
			cout << (n+m)/g << endl;
		}
	}
	return 0;
}