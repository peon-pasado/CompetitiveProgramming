#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 10;
bool composite[maxn];
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
	sieve(5e4);
	int n;
	while (scanf("%d", &n), n) {
		printf("%d =", n);
		bool fst = 1;
		if (n < 0) {
			printf(" -1");
			fst = 0;
			n = -n;
		}
		for (int p : prime) {
			if (p *1ll* p > n) break;
			if (n % p == 0) {
				while (n % p == 0) {
					if (fst) {
						printf(" %d", p);
						fst = 0;
					} else {
						printf(" x %d", p);
					}
					n /= p;
				}
			}
		}
		if (n > 1) {
			if (fst) {
				printf(" %d", n);
			} else {
				printf(" x %d", n);
			}
		}
		puts("");
	}
	return 0;
}