#include <bits/stdc++.h>
using namespace std;

bool check(long long n, long long k, long long d) {
	return (n/d) >= k * (k + 1) / 2;
}

int main() {
	long long n, k;
	cin >> n >> k;
	if (k >= 2e5) {
		return puts("-1"), 0;
	}
	bool ok = 0;
	long long maxi = -1;
	for (long long i = 1; i*i <= n; ++i) {
		if (n % i == 0) {		
			if (check(n, k, i)) {
				ok = 1;
				maxi = i;
			}
			if (check(n, k, n/i)) {
				ok = 1;
				maxi = n/i;
				break;
			}
		}
	}
	if (ok) {
		for (int i = 1; i < k; ++i) {
			cout << maxi * i << " ";
		}
		cout << maxi * (n/maxi - k*1ll*(k-1)/2) << endl;
	} else {
		puts("-1");
	}
	return 0;
}