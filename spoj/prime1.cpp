#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
bool composite[maxn];
bool res[maxn];
vector<int> prime;

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
	sieve(1e5);
	int t;
	scanf("%d", &t);
	while (t--) {
		long long m, n;
		scanf("%lld %lld", &m, &n);
		memset(res, 0, sizeof res);
		if (m == 1) res[0] = 1;
		for (int p : prime) {
			for (long long i = max(2ll * p, (m + p - 1) / p * p); i <= n; i += p) {
				res[i - m] = 1;
			}
		}
		for (int i = 0; i <= n - m; ++i) {
			if (res[i] == 0) {
				printf("%lld\n", m + i);
			}
		}
		if (t) puts("");
	}
	return 0;
}