#include <iostream>
using namespace std;

const int maxn = 20;
const int mod = 1e9 + 7;
int a[1000'010];
int F[1<<maxn];

int qpow(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = r*1ll*a%mod;
		a = a*1ll*a%mod;
		b >>= 1;
	}
	return r;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		int k;
		cin >> k;
		int mask = 0;
		for (int i = 0; i < k; ++i) {
			int x;
			cin >> x;
			mask |= 1<<x;
		}
		F[mask>>1]++;
	}
	for (int i = 0; i < m; ++i) 
		for (int s = 0; s < 1<<m; ++s)
			if (s&(1<<i))
				F[s] += F[s^(1<<i)];

	for (int s=0; s<1<<m; ++s)
		if (__builtin_popcount(s)&1) F[s] = (qpow(2, F[s]) + mod - 1) % mod;
		else F[s] = (mod - qpow(2, F[s]) + 1) % mod;
	
	for (int i = 0; i < m; ++i) 
		for (int s = 0; s < 1<<m; ++s)
			if (s&(1<<i)) {
				F[s] += F[s^(1<<i)];
				if (F[s] >= mod) F[s] -= mod;
			}
	
	for (int s=0; s<1<<m; ++s)
		if (__builtin_popcount(s)%2 == 0)
			F[s] = mod - F[s];

	cout << F[(1<<m)-1]%mod << '\n';
	return 0;
}