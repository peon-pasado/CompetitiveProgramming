#include <bits/stdc++.h>
using namespace std;

int main() {

	int n, m, t;
	cin >> m >> n >> t;

	long long time = 1;
	bool ok = 1;
	if (t == 1) {
		for (int i = 1; i <= n; ++i) {
			time *= i;
			if (time > m) {
				ok = 0;
				break;
			}
		}
	} else if (t == 2) {
		for (int i = 1; i <= n; ++i) {
			time <<= 1;
			if (time > m) {
				ok = 0;
				break;
			}
		}
	} else if (t == 3) {
		if (n >= 1000) ok = 0;
		else {
			time = 1ll * n * n * n * n;
			if (time > m) ok = 0;
		}
	} else if (t == 4) {
		if (n > 1000) ok = 0;
		else {
			time = 1ll * n * n * n;
			if (time > m) ok = 0;
		}
	} else if (t == 5) {
		if (n > 40000) ok = 0;
		else {
			time = 1ll*n*n;
			if (time > m) ok = 0;
		}
	} else if (t == 6) {
		if (n * log2(n) - 1e-8 > m) ok = 0;  
	} else {
		if (n > m) ok = 0;
	}

	puts(ok ? "AC" : "TLE");

	return 0;
}