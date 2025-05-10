#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	if (a == b) cout << "infinity" << endl;
	else {
		int t = abs(a-b);
		int res = 0;
		for (int d = 1; d*d <= t; ++d) {
			if (t % d == 0) {
				res += a % d == b;
				if (d*d != t) res += a % (t/d) == b;
			}	
		}
		cout << res << endl;
	}
	return 0;
}