#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int smod = mod - 1;
const int maxN = 2e5 + 10;
int cnt[maxN];

int add(int a, int b, int mod) {
	return (a+b)%mod;
}

int mul(long long a, long long b, int mod) {
	return a * b % mod;
}

int ex(int a, int b, int mod) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = mul(r, a, mod);
		a = mul(a, a, mod);
		b >>= 1;
	}
	return r;
}

int main() {
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int p;
		scanf("%d", &p);
		cnt[p] += 1;
	}
	bool perfectSquare = 1;
	for (int i = 2; i < maxN; ++i) {
		if (cnt[i] & 1) {
			perfectSquare = 0;
			break;
		}
	}
	int n = 1, sigma = 1;
	if (perfectSquare) {
		for (int i = 2; i < maxN; ++i) {		
			if (cnt[i] > 0) {
				n = mul(n, ex(i, cnt[i]>>1, mod), mod);
				sigma = mul(sigma, cnt[i] + 1, smod);
			}
		}
	} else {
		bool firstEven = 1;
		for (int i = 2; i < maxN; ++i) {
			if (cnt[i] > 0) {
				n = mul(n, ex(i, cnt[i], mod), mod);
				if ((cnt[i]&1) and firstEven) {
					firstEven = 0;
					sigma = mul(sigma, (cnt[i] + 1) / 2, smod);
				} else {
					sigma = mul(sigma, cnt[i] + 1, smod);
				}
			}
		}
	}
	printf("%d\n", ex(n, sigma, mod));
	return 0;
}