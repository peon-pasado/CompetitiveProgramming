#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool composite[maxn];
vector<int> prime;
long long f[maxn];
int pot[maxn];

void sieve(int n) {
	f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
			f[i] = 1 + i *1ll* (i - 1);
			pot[i] = i;
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				f[p * i] = f[i / pot[i]] * (f[pot[i]] + pot[i] *1ll* pot[i] * p * (p - 1));
				pot[p * i] = p * pot[i];
				break;
			} else {
				f[p * i] = f[p] *1ll* f[i];
				pot[p * i] = p;
			}
		}
	}
}

int main() {
	int t;
	cin >> t;
	sieve(1e6);
	while (t--) {
		int n;
		cin >> n;
		cout << (1 + f[n]) * n / 2 << endl;
	}
	return 0;
}