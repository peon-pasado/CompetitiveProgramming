#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
int F[2][1<<maxn];
string a;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q >> a;
	for (auto& c : a) c -= '0';
	for (int i = 0; i < 2; ++i) {
		for (int s = 0; s < 1<<n; ++s)
			F[i][s] = a[s];
		for (int j = 0; j < n; ++j)
			for (int s = 0; s < 1<<n; ++s)
				if (((s>>j)&1) == i)
					F[i][s] += F[i][s^(1<<j)];
	}
	while (q--) {
		string s;
		cin >> s;
		reverse(s.begin(), s.end());
		int n0=0, n1=0, ni=0;
		int m0=0, m1=0, mi=0;
		for (int i = 0; i < n; ++i) {
			n0 += s[i] == '0'; m0 += (s[i]=='0')<<i;
			n1 += s[i] == '1'; m1 += (s[i]=='1')<<i;
			ni += s[i] == '?'; mi += (s[i]=='?')<<i;
		}
		int ans = 0;
		if (ni <= min(n0, n1)) {
			ans = a[m1];
			for (int s = mi; s > 0; s = mi & (s-1)) {
				ans += a[s | m1];
			}
		} else if (n0 <= min(n1, ni)) {
			ans = F[0][m1];
			for (int s = m0; s > 0; s = m0 & (s-1)) {
				if (__builtin_popcount(s)&1) ans -= F[0][m1 | s];
				else ans += F[0][m1 | s];
			}
		} else {
			if (0 != n1%2) ans = -F[1][mi];
			else ans = F[1][mi];
			for (int s = m1; s > 0; s = m1 & (s-1)) {
				if ((__builtin_popcount(s)&1) != n1%2) ans -= F[1][mi | s];
				else ans += F[1][mi | s];
			}
		}
		cout << ans << '\n';
	}
	
	return 0;
}