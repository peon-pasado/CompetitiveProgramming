#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef unsigned long long ull;
typedef long double ld;

ull mod_mul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(ld(a) * ld(b) / ld(M));
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull mod_pow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = mod_mul(b, b, mod), e /= 2)
		if (e & 1) ans = mod_mul(ans, b, mod);
	return ans;
}

ull ctz(ull x) {
	int cnt = 0;
	for (int i = 0;; ++i) {
		if (x & (1ull<<i)) break;
		cnt++;
	}
	return cnt;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	ull s = ctz(n-1);
	ull d = n >> s;
	for (int j = 0; j < 7; ++j) {   // ^ count trailing zeroes
		ull p = mod_pow(A[j]%n, d, n);
		int i = s;
		while (p != 1 && p != n - 1 && A[j] % n && i--)
			p = mod_mul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

ull f(ull x, ull n) {
	return mod_mul(x, x, n) + 1;
} 

ull gcd(ull a, ull b) {
	return b==0?a:gcd(b, a%b);
}

ull pollard(ull n) {
	ull x = 0, y = 0, t = 0, prd = 2, i = 1, q;
	while (t++ % 40 || gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x, n);
		if ((q = mod_mul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x, n), y = f(f(y, n), n);
	}
	return gcd(prd, n);
}

void factor(ull n, vector<ull>& f) {
	if (n == 1) return;
	if (isPrime(n)) {
		f.push_back(n);
		return;
	}
	ull x = pollard(n);
	factor(x, f); 
	factor(n / x, f);
}

ull AA[66000];
int LOG[66000];
int int_log(int x) {
	if (x == 1) return 0;
	if (LOG[x]) return LOG[x];
	return LOG[x] = int_log(x/2) + 1;
}

int main() {
	//sieve();
	ull g, l;
	while (scanf("%llu %llu", &g, &l) == 2) {
		vector<ull> f;
		ull n = l / g;
		if (n == 1) {
			printf("%llu %llu\n", g, g);
			continue;
		}
		factor(n, f);
		sort(all(f));
		int j = 0;
		for (int i = 1; i < sz(f); ++i) {
			if (f[j] % f[i] == 0) {
				f[j] *= f[i];
			} else {
				f[++j] = f[i];
			}
		}
		f.resize(j+1);
		ull ans = 5e18, x, y;
		AA[0] = g;
		for (int s = 2; s < 1<<sz(f); s += 2) {
			int pos = int_log(s & -s);
			AA[s] = AA[s ^ (s&-s)] * f[pos];
			ull a = AA[s];	
			ull b = l / a * g;
			if (ans > a+b) {
				ans = a + b;
				x = a; y = b;
			}
		}
		if (x > y) swap(x, y);
		printf("%llu %llu\n", x, y);
	}
	return 0;
}