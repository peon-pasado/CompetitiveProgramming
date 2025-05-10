#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool composite[maxn];
vector<int> prime;
int d[maxn], ex[maxn];

void sieve(int n) {
	d[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
			d[i] = 2;
			ex[i] = 1;
		}
		for (int p : prime) {
			if (i * p > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				d[p * i] = d[i] / (ex[i] + 1) * (ex[i] + 2);
				ex[p * i] = ex[i] + 1;
				break;
			} else {
				d[p * i] = 2 * d[i];
				ex[p * i] = 1;
			}
		}
	}
}

int main() {
	sieve(1e6);
	int t;
	scanf("%d\n", &t);
	while (t--) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", d[__gcd(a, b)]);
	}
	return 0;
}