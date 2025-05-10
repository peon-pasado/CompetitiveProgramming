#include <bits/stdc++.h>
using namespace std;

const int maxn = 1<<20;
const int mod = 1e9 + 7;
int F[3][maxn];

int main() {
	int n;
	cin >> n;
	for (int k = 0; k < 3; ++k) {
		for (int i = 0; i < 1<<n; ++i) 
			cin >> F[k][i];
		for (int i = 0; i < n; ++i)
			for (int s = 0; s < 1<<n; ++s)
				if (s & (1<<i))
					(F[k][s] += F[k][s^(1<<i)]) %= mod;
	}
	for (int s = 0; s < 1<<n; ++s) {
		F[0][s] = F[0][s] *1ll* F[1][s] % mod;
		F[0][s] = F[0][s] *1ll* F[2][s] % mod;
	}
	for (int s = 0; s < 1<<n; ++s)
		if (__builtin_popcount(s)%2 == 0) 
			F[0][s] = mod - F[0][s];
	for (int i = 0; i < n; ++i) 
		for (int s = 0; s < 1<<n; ++s)
			if (s & (1<<i))
				(F[0][s] += F[0][s^(1<<i)]) %= mod;
	for (int i = 0; i < 1<<n; ++i)
		if (__builtin_popcount(i)%2 == 0) 
			F[0][i] = mod-F[0][i];
	for (int i = 0; i < n; ++i)			
		for (int s = 0; s < 1<<n; ++s)
			if (~s & (1<<i))
				(F[0][s] += F[0][s^(1<<i)]) %= mod;
	int ans = 0;
	for (int i = 0; i < 1<<n; ++i) {
		(ans += F[0][i]) %= mod;
	}
	cout << ans << '\n';
	return 0;
}