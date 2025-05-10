#include <bits/stdc++.h>
using namespace std;

bitset<10000001> composite;
vector<int> prime;
int sqf[10000001];
void sieve(int n) {
	composite[0] = composite[1] = 1;
	sqf[1] = 1;
	int t = 1;
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.emplace_back(i);
			sqf[i] = 1;
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				sqf[p * i] = sqf[i] and i % (p *1ll* p);
				break;
			} else {
				sqf[p * i] = sqf[i];
			}
		}
		if (sqf[i]) {
			sqf[i] = ++t;
		}
	}
}

int main() {
	sieve(1e7);	
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; ++tc) {
		int n;
		scanf("%d", &n);
		if (sqf[n]) {
			printf("Case %d: %d\n", tc, sqf[n]);
		} else {
			printf("Case %d: Not Cube Free\n", tc);	
		}
	}
	return 0;
}