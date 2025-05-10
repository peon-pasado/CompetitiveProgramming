#include <bits/stdc++.h>
using namespace std;
const int maxN = 30;
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
int b[10];
int a[maxN];
int n, k;
int dp[1<<24];
int sum[1<<24];


int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	cin >> k;
	for (int i = 0; i < k; ++i) cin >> b[i];
	
	for (int mask = 1; mask < 1<<n; ++mask) {
		int lso = mask & -mask;
		int i = 31 - __builtin_clz(lso);
		sum[mask] = min(inf, a[i] + sum[mask ^ lso]);
	}	
	if ((k >= 1 and sum[(1<<n)-1] == b[0]) or (k >= 2 and sum[(1<<n)-1] == b[1])) return cout << 0 << endl, 0;
	dp[(1<<n)-1] = 1;
	for (int mask = (1<<n)-2; mask >= 0; --mask) {
		if (k >= 1 and sum[mask] == b[0]) dp[mask] = 0;
		else if (k >= 2 and sum[mask] == b[1]) dp[mask] = 0;
		else {
			int& ans = dp[mask] = 0;
			for (int i = 0; i < n; ++i) {
				if ((~mask >> i) & 1) {
					ans += dp[mask | (1<<i)];
					if (ans > mod) ans -= mod;
				}	
			}
		}
	}
	cout << dp[0] << endl;
	return 0;
}