#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
bool composite[maxn];
vector<int> prime;
int d[maxn], ex[maxn];

void sieve(int n) {
	d[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!composite[i]) {
			prime.emplace_back(i);
			d[i] = 2;
			ex[i] = 1;
		}	
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				d[p * i] = d[i] / (ex[i] + 1) * (ex[i] + 2);
				ex[p * i] = ex[i] + 1;
				break;
			} else {
				d[p * i] = 2 * d[i];
				ex[p * i] = 1;
			}
		}
	}
} 

int main() {
	int a, b, c;
	cin >> a >> b >> c;
	sieve(1e6);
	int ans = 0;
	for (int i = 1; i <= a; ++i) {
		for (int j = 1; j <= b; ++j) {
			for (int k = 1; k <= c; ++k) {
				ans = (ans + d[i * j * k]) & ((1<<30) - 1); 
			}
		}
	}
	cout << ans << endl;
	return 0;
}