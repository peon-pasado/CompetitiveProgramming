#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
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
	sieve(1e6);
	int t;
	scanf("%d", &t);
	for (int nc = 1; nc <= t; ++nc) {
		int a, b;
		long long l;
		scanf("%d %d %lld", &a, &b, &l);
		long long c = 1;
		bool fun = 1;
		for (int p : prime) {
			long long na = 1, nb = 1, nl = 1;
			if (a % p == 0) {
				while (a % p == 0) {
					na *= p;
					a /= p;
				}
			}
			if (b % p == 0) {
				while (b % p == 0) {
					nb *= p;
					b /= p;
				}
			}
			if (l % p == 0) {
				while (l % p == 0) {
					nl *= p;
					l /= p;
				}
			}
			
			if (max(na, nb) > nl) {
				fun = 0;
				break;	
			}
			if (max(na, nb) < nl) c *= nl; 
		}
		printf("Case %d: ", nc);
		if (fun) printf("%lld\n", c);
		else puts("impossible");
	}
	return 0;
}