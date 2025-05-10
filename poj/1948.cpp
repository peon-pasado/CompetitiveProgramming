#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;

const int maxn = 1610;
bitset<maxn> dp[maxn];

long long bi_sqrt(long long x) {
	long long lo = 0, hi = 1e9;
	while (lo < hi) {
		long long mid = (lo + hi + 1) / 2;
		if (mid*mid <= x) lo = mid;
		else hi = mid-1;
	}
	return lo;
}

int main() {
	int n;
	cin >> n;
	dp[0][0] = 1;
	int tot = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		tot += x;
		for (int a = maxn-1; a >= 0; --a) {
			if (a >= x) dp[a] |= (dp[a-x] | (dp[a] << x));
			else dp[a] |= (dp[a] << x);
		}
	}
	long long ans = 0;
	for (int i = 0; i < maxn; ++i) {
		for (int j = 0; j < maxn; ++j) {
			int k = tot - i - j;
			if (k < 0) break;
			if (dp[i][j]) {
				ans = max(ans, tot *1ll* (tot - 2*i) * (tot - 2*j) * (tot - 2*k));
			}
		}	
	}
	ans *= 625;
	if (ans == 0) cout << -1 << '\n';
	else cout << bi_sqrt(ans) << '\n';
	return 0;
}