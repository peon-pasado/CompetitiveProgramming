#include <bits/stdc++.h>
#define all(V) V.begin(), V.end()
using namespace std;
const int maxn = 1e6 + 10;
bool composite[maxn];
vector<int> prime;
vector<int> f[15];
int pf[maxn];

void sieve(int n) {
	f[0].push_back(1);
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
			pf[i] = 1;
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				pf[p * i] = pf[i];
				break;
			} else {
				pf[p * i] = pf[i] + 1;
			}
		}
		f[pf[i]].push_back(i);
	}
}

int query(int x, int l, int r) {
	return upper_bound(all(f[x]), r) - lower_bound(all(f[x]), l);
}

int main() {
	sieve(1e6);
	int t;
	scanf("%d", &t);
	while (t--) {
		int a, b, n;
		cin >> a >> b >> n;
		cout << query(n, a, b) << endl;
	}
	return 0;
}