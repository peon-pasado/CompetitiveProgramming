#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool composite[maxn];
vector<int> prime;

void sieve(int n) {
	composite[1] = 1;
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
	sieve(1e6);
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%d ", n);
		if (composite[n]) puts("is not prime.");
		else {
			int t = n, r = 0;
			while (t > 0) {
				r = r * 10 + t % 10;
				t /= 10;
			}
			if (n == r or composite[r]) puts("is prime.");
			else puts("is emirp.");
		}
	}
	return 0;
}