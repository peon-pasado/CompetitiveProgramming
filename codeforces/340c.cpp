#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
	return b ? gcd(b, a%b) : a;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int& x : a) cin >> x;
	sort(a.begin(), a.end());
	vector<long long> sum(n + 2);
	for (int i = 1; i <= n; ++i) {
		sum[i] = a[i-1] + sum[i-1];
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		long long temp = 0;
		temp += (sum[n] - sum[i]) - (n - i) *1ll* a[i - 1];
		temp += (i - 1) *1ll* a[i - 1] - sum[i-1];
		temp += a[i - 1];
		ans += temp;
	}
	long long g = gcd(ans, n);
	cout << ans / g << " " << n / g << endl;
 	return 0;
}