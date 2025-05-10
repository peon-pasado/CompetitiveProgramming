#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
const int mod = 1e9 + 7;
int a[1<<maxn];
int F[1<<maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		memset(a, 0, sizeof a);
		for (int i = 0; i < n; ++i) {
			int x;
			cin >> x;
			a[x]++;
		}
		for (int i = 0; i < 1<<20; ++i)
			F[i] = a[i];
		for (int i = 0; i < 20; ++i)
			for (int s = 0; s < 1<<20; ++s)
				if (s&(1<<i))
					F[s] += F[s^(1<<i)];
		long long ans = 0;
		for (int i = 0; i < 1<<20; ++i)			
			if (a[i])
				ans += F[i]*1ll*a[i];
		cout << ans << '\n';
	}
	return 0;
}