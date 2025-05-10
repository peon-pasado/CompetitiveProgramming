#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
long double Log[maxn];

int main() {
	for (int i = 1; i < maxn; ++i) {
		Log[i] = Log[i-1] + log2(i);
	}
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; ++tc) {
		cout << "Case " << tc << ": ";
		int n, d;
		cin >> n >> d;
		cout << int(floor(Log[n] / log2(d) + 1 + 1e-8)) << endl;
	}
	return 0;
}