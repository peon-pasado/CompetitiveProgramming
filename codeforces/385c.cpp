#include <bits/stdc++.h>
using namespace std;
const int maxp = 1e7 + 10;
bool composite[maxp];
vector<int> prime;

void sieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (!composite[i]) {
			prime.emplace_back(i);
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) break;
		}
	}
}
int cnt[maxp];

int main() {
	sieve(1e7);	
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		cnt[x] += 1;
	}
	for (int p : prime) {
		for (int j = 2 * p; j < maxp; j += p) {
			cnt[p] += cnt[j];
		}
	}
	for (int i = 2; i < maxp; ++i) {
		if (composite[i]) {
			cnt[i] = cnt[i-1];
		} else {
			cnt[i] += cnt[i-1];
		}
	}
	int m;
	cin >> m;
	while (m--) {
		int l, r;
		cin >> l >> r;
		if (l >= maxp) cout << 0 << endl;
		else cout << (cnt[min(r, maxp-1)] - cnt[l-1]) << endl;
	}
	return 0;
}