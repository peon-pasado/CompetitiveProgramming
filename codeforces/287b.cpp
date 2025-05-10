#include <bits/stdc++.h>
using namespace std;
long long n, k;

long long p(long long x) {
	return k * (k + 1) / 2 - (k-x) * (k-x+1) / 2 - x + 1; 
}

int main() {
	cin >> n >> k;
	long long lo = 0, hi = k-1;
	while (lo < hi) {
		long long mid = lo + (hi - lo) / 2;
		if (p(mid) < n) lo = mid + 1;
		else hi = mid;
	}
	if (p(lo) >= n) cout << lo << endl;
	else cout << -1 << endl;
	return 0;
}