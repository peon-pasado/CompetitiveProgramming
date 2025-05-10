#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(long long a, long long b) {
	return a*b%mod;
}

int ex(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

const int maxn = 1e6 + 10;
int memo[maxn];
bool vis[maxn];
int calc(int n) {
	if (vis[n]) return memo[n];
	vis[n] = 1;
	return memo[n] = mul(n, ex(2, n-1));
}

bool composite[maxn];
vector<int> prime;
int mu[maxn];
int cnt[maxn];

void sieve(int n) {
	mu[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!composite[i]) {
			prime.emplace_back(i);
			mu[i] = -1;
		}	
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) {
				mu[p * i] = 0;
				break;
			} else {
				mu[p * i] = -mu[i];
			}
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& x : a) {
		cin >> x;
		cnt[x] += 1;
	}
	for (int i = 1; i <= 1000000; ++i) {
		for (int j = 2 * i; j <= 1000000; j += i) {
			cnt[i] += cnt[j];
		}
	}
	sieve(1e6);
	int ans = 0;
	for (int i = 2; i <= 1000000; ++i) {
		int temp = 0;
		for (int j = i; j <= 1000000; j += i) {
			temp = add(temp, mul(mod + mu[j/i], calc(cnt[j])));
		}
		ans = add(ans, mul(i, temp));
	}
	cout << ans << endl;
	return 0;
}