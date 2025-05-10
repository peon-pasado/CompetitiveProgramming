#include <bits/stdc++.h>
using namespace std;

bool compare(int x, int y) {
	int cnt[10];
	memset(cnt, 0, sizeof cnt);
	while (x > 0) {
		cnt[x%10] = 1;
		x /= 10;
	}
	while (y > 0) {
		if (cnt[y%10]) return 1;
		y /= 10;
	}
	return 0;
}

int main() {
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 1; i*i <= n; ++i) {
		if (n % i == 0) {
			ans += compare(i, n);
			if (i*i != n) {
				ans += compare(n/i, n);
			}
		}
	}
	cout << ans << endl;
	return 0;
}