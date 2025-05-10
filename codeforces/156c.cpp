#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxN = 3e3 + 10;

int add(int a, int b) {return (a+b)%mod;}
int mul(long long a, long long b) {return a*b%mod;}

int f[maxN], fi[maxN], r[maxN];
int n;
int co(int n, int k) {
	if (n < k) return 0;
	return mul(f[n], mul(fi[k], fi[n-k]));
}

int main() {
	f[0] = 1;
	for (int i = 1; i < maxN; ++i) f[i] = mul(f[i-1], i);
	r[1] = 1;
	for (int i = 2; i < maxN; ++i) r[i] = mul(r[mod%i], mod - mod/i);
	fi[0] = 1;
	for (int i = 1; i < maxN; ++i) fi[i] = mul(fi[i-1], r[i]);
	
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		int C = 0;
		for (int i = 0; i < s.size(); ++i) C += s[i] - 'a';
		int ans = 0;
		int n = s.size();
		for (int i = 0; i <= n; ++i) {	
			int temp = mul(co(n, i), co(C - 26 * i + n - 1, n - 1));
			if (i%2 == 0) ans = add(ans, temp);
			else ans = add(ans, mod - temp);
		}
		cout << (ans + mod - 1) % mod << endl;
	}
	return 0;
}