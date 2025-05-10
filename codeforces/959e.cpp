#include <bits/stdc++.h>
using namespace std;

int main() {
	long long n;
	cin >> n;
	long long sum = 0;
	for (int i = 0; i <= 63 - __builtin_clzll(n - 1); ++i) {
		sum += (n - 1 - (1ll<<i) >> i+1) + 1 << i;
	}
	cout << sum << endl;
	return 0;
}