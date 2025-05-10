#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
bool composite[maxn];
vector<int> prime;
const int mod = 1e9 + 7;

void sieve(int n) {
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

int mul(long long a, long long b) {
	return a * b % mod;
}

int add(int a, int b) {
	return (a + b) % mod;
}

int ex(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = r * 1ll * a % mod;
		a = a * 1ll * a % mod;
		b >>= 1;
	}
	return r;
}

int main() {
	sieve(1e5);
	int t;
	scanf("%d", &t);
	for (int nc = 1; nc <= t; ++nc) {
		long long n, m;
		cin >> n >> m;
		int ans = 1;
		for (int p : prime) {
			if (p *1ll* p > n) break;
			if (n % p == 0) {
				int e = 0;
				while (n % p == 0) {
					e += 1;
					n /= p;
				}
				int temp = add(ex(p, (e * 1ll * m + 1) % (mod - 1)), mod - 1);
				temp = mul(temp, ex(p - 1, mod - 2));
				ans = mul(ans, temp);
			}
		}
		if (n > 1) ans = mul(ans, mul(add(ex(n, (m + 1ll) % (mod - 1)), mod - 1), ex(n - 1, mod - 2)));
		printf("Case %d: %d\n", nc, ans);
	}
	return 0;
}