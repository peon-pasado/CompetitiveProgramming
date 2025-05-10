#include <bits/stdc++.h>
using namespace std;

bool test(int x, int y) {
	int m = (4*x + 9*y - 49);
	if (m < 0) return true;	
	if (m % 9 == 0) return false;
	if (m % 4 == 0) return false;	
	for (int a = 1; a <= 8; ++a) {
		for (int b = 1; b <= 48; ++b) {
			if (4*a + 9*b == m) return false;
		}
	}
	return true;
}

int main() {
	int n;
	cin >> n;
	long long ans = 0;
	for (int i = 0; i <= 8; ++i) {
		for (int j = 0; j <= 48; ++j) {
			if (test(i, j)) {
			 	ans += max(0ll, n - i - j + 1ll);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
