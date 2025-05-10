#include <bits/stdc++.h>
using namespace std;

int add(int a, int b, int mod) {
	return (a + b) % mod;
}

int mul(long long a, long long b, int mod) {
	return a * b % mod;
}

int ex(int a, long long b, int mod) {
	int r = 1;
	while (b>0) {
		if (b&1) r = mul(r, a, mod);
		a = mul(a, a, mod);
		b >>= 1;
	}
	return r;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int k, p;
		long long l, r;
		cin >> k >> l >> r >> p;
		if (k%2 == 0) {
			if (p == 2) {
				cout << 1 << endl;
			} else {
				int A = ex(k, ex(2, r+1, p-1), p);
				A = add(A, p-1, p);
				int B = ex(k, ex(2, l, p-1), p);
				B = add(B, p-1, p);
				if (k%p == 0) {
					A = B = p-1;
				}
				if (B == 0) {
					//k^2^l == 1 (mod p)
					cout << ex(2, r-l+1, p) << endl;
				} else {
					cout << mul(A, ex(B, p-2, p), p) << endl;
				}
			}
			//(k^2^(r+1) - 1) / (k^2^l - 1)
		} else if (p != 2) {
			int A = ex(k, ex(2, r+1, p-1), p);
			A = add(A, p-1, p);
			int B = ex(k, ex(2, l, p-1), p);
			B = add(B, p-1, p);
			if (k%p == 0) {
				A = B = p-1;
			}
			if (B == 0) {
				cout << 2 << endl;
			} else {
				B = mul(B, ex(2, r-l, p), p);
				cout << mul(A, ex(B, p-2, p), p) << endl;
			}
			//(k^2^(r+1) - 1) / ((k^2^l - 1) x 2^(r-l)) 
		} else cout << 0 << endl;
	}
	return 0;
}