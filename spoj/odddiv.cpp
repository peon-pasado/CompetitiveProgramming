#include <bits/stdc++.h>
#define all(V) V.begin(), V.end()
using namespace std;
const int maxn = 1e5 + 10;
bool composite[maxn];
vector<int> prime;
int d[maxn];
int ex[maxn];
vector<long long> T[maxn];

void sieve(int n) {
	d[1] = 1;
	T[1].push_back(1);
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
			d[i] = 3;
			ex[i] = 1;
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				d[p * i] = d[i] / (2 * ex[i] + 1) * (2 * ex[i] + 3);
				ex[p * i] = ex[i] + 1;
				break;
			} else {
				d[p * i] = d[i] * 3;
				ex[p * i] = 1;
			}
		}
		T[d[i]].push_back(i * 1ll* i);
	}
}

int query(int k, long long l, long long r) {
	return upper_bound(all(T[k]), r) - lower_bound(all(T[k]), l);
}

int main() {
	sieve(1e5);
	int t;
	scanf("%d", &t);
	while (t--) {
		long long k, l, r;
		scanf("%lld %lld %lld", &k, &l, &r);
		printf("%d\n", query(k, l, r));
	}
	return 0;
}