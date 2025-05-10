#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
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
	sieve(1e6);
	int n;
	while (cin >> n, n) {
		int a, b;
		for (int p : prime) {
			if (not composite[n - p]) {
				a = p;
				b = n - p;
				break;
			}
		}
		cout << n << " = " << a << " + " << b << endl;
	}
	return 0;
}