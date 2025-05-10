#include <iostream>
using namespace std;

int mod_pow(int a, int b, int m) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = r*1ll*a%m;
		a = a*1ll*a%m;
		b >>= 1;
	}
	return r;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int m, h;
		cin >> m >> h;
		int ans = 0;
		for (int i = 0; i < h; ++i) {
			int a, b;
			cin >> a >> b;
			ans = (ans + mod_pow(a, b, m)) % m;
		}
		cout << ans << endl;
	}
	return 0;
}