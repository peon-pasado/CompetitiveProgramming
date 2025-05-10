#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
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
	sieve(1e3);
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d\n", &n);
		puts("1");
		for (int p : prime) {
			if (p > n) break;
			printf("%d\n", p);
		}
		if (t) puts("");
	}
	return 0;
}