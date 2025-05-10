#include <bits/stdc++.h>
using namespace std;

bitset<10000001> composite;
vector<int> prime;
void sieve(int n) {
	composite[0] = composite[1] = 1;
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
	sieve(1e7);	
	int t;
	scanf("%d", &t);
	for (int tc = 1; tc <= t; ++tc) {
		int n;
		scanf("%d", &n);
		int ans = 0;
		for (int p : prime) {
			if (p > n>>1) break; 
			ans += not composite[n - p];
		}
		printf("Case %d: %d\n", tc, ans);
	}
	return 0;
}