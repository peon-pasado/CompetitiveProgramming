#include <bits/stdc++.h>
using namespace std;

const int maxn = 1<<20;
int F[maxn];
int a[maxn], b[maxn];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		memset(F, 0, sizeof F);
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			F[a[i]] += 1;
		}
		n = 0;
		for (int i = 0; i < 1<<20; ++i)
			if (F[i]) {
				a[n] = i; 
				b[n] = F[i];
				n += 1;
			}
		for (int i = 0; i < 20; ++i)
			for (int s = 0; s < 1<<20; ++s)
				if (s&(1<<i))
					F[s] += F[s^(1<<i)];
		long long ans = 0;
		for (int i = 0; i < n; ++i) {
			int t = F[a[i]];
			ans += b[i] *1ll* (t - b[i]) + b[i] *1ll* (b[i] - 1) / 2;
		}
		cout << ans << '\n';
	}
	return 0;
}