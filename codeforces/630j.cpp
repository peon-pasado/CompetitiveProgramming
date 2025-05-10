#include <bits/stdc++.h>
using namespace std;

int main() {
	int f = 1;
	for (int i = 2; i <= 10; ++i) {
		f *= i / __gcd(f, i);
	}
	long long n;
	cin >> n;
	cout << n / f << endl;
	return 0;
}