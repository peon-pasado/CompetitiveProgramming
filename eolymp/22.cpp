#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
bool composite[maxn];
vector<int> prime;

void sieve(int n) {
	composite[1] = 1;
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
	sieve(1e5);
	int l, r;
	cin >> l >> r;
	int ans = 0;
	for (int i = l; i <= r; ++i) {
		if (not composite[i]) {
			int t = i, r = 0;
			while (t > 0) {
				r = r * 10 + t % 10;
				t /= 10;
			}
			ans += not composite[r];
		}
	}
	cout << ans << endl;
	return 0;
}