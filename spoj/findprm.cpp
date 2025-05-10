#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 10;
bool composite[maxn];
vector<int> prime;
int res[maxn];

void sieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.emplace_back(i);
			res[i] += 1;
			if (2 * i <= n) {
				res[2 * i] -= 1;
			}
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) break;
		}
		res[i] += res[i-1];
	}
}

int main() {
	sieve(1e7);
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", res[n]);
	}
	return 0;
}