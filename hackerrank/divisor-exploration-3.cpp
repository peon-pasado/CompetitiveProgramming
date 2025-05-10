#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
bool composite[maxn];
vector<int> prime;
int coef[1010][2010];

void sieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.emplace_back(i);
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) break;
		}
	}
}

int main() {
	coef[0][0] = 1;
	for (int i = 1; i <= 1000; ++i) {
		for (int j = 0; j <= 2000; ++j) {
			coef[i][j] = coef[i-1][j];
			if (j > 0) {
				coef[i][j] += coef[i][j-1];
				if (coef[i][j] >= mod) {
					coef[i][j] -= mod;
				}
			}
		}
	}
	sieve(1e5);
	int q;
	cin >> q;
	while (q--) {
		int m, a, d;
		cin >> m >> a >> d;
		int ans = 1;
		for (int i = 0; i < m; ++i) {
			int ex = i + a + 1;
			int p_pot = 1;
			int lans = 0;
			for (int j = ex; j >= 0; --j) {
				lans = (lans + coef[d-1][j] *1ll* p_pot % mod) % mod;
				p_pot = p_pot *1ll* prime[i] % mod;
			}
			ans = ans *1ll* lans % mod;
		}
		cout << ans << endl;
	}
	return 0;
}