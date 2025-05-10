#include <bits/stdc++.h>
using namespace std;

long long d(long long n) {
	int sum = 0;
	while (n>0) {
		sum += n%10;
		n/=10;
	}
	return sum;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		long long n;
		cin >> n;
		long long x = n;
		if (__gcd(x, d(x)) > 1) cout << x << '\n';
		else if (__gcd(x+1, d(x+1)) > 1) cout << x+1 << '\n';
		else cout << x + 2 << '\n';
	}
	return 0;
}