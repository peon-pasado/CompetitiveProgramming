#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool composite[maxn];
vector<int> prime;

void sieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) break;
		}
	}
}


int main() {
	sieve(1e6);
	int t;
	scanf("%d", &t);
	while (t--) {
		long long n;
		scanf("%lld", &n);
		long long ans = 0;
		for (int p : prime) {
			if (p*1ll*p > n) break;
			if (n % p == 0) {
				while (n % p == 0) {
					n /= p;
				}
				ans = max(ans, 1ll*p);
			}
		}
		ans = max(ans, n);
		printf("%lld\n", ans);
	}
	return 0;
}