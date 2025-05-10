#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int ans = 0;
	for (int l = 0; l < n; ++l) {
		for (int r = l; r < n; ++r) {
			for (int i = l; i <= r; ++i) a[i] = 1 - a[i];
			int contar1 = 0;
			for (int i = 0; i < n; ++i) {
				if (a[i] == 1) {
					contar1 += 1;
				}
			}
			ans = max(ans, contar1);
			for (int i = l; i <= r; ++i) a[i] = 1 - a[i];
		}
	}
	cout << ans << endl;
	return 0;
}