#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main() {
	int n;
	cin >> n;
	long long res = 1;
	for (int i = 2; i <= n; ++i) {
		res = res / gcd(res, i) * i;
	}
	cout << res << endl;
	return 0;
}