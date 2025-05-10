#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		long long ans = 0;
		ans += (1ll<<n+1) - 2;
		ans -= 2 * (1ll<<n);
		for (int i = 1; i <= n/2 - 1; ++i) {
			ans -= 2 * (1ll<<i);
		}
		ans = abs(ans);
		cout << ans << endl;
	}
	return 0;
}