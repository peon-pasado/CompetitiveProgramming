#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
long long sum[2][26][maxn];

int main() {
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;
	for (int i = 0; i < n; ++i) {
		sum[0][a[i] - 'A'][i] = i + 1;
		sum[1][a[i] - 'A'][i] = n - i;
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 26; ++j) {
			sum[0][j][i] += sum[0][j][i-1];
		}
	}
	for (int i = n-2; i >= 0; --i) {
		for (int j = 0; j < 26; ++j) {
			sum[1][j][i] += sum[1][j][i+1];
		}
	}
	long double ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += (i + 1) *1ll* sum[1][b[i] - 'A'][i + 1];
		ans += (n - i) *1ll* sum[0][b[i] - 'A'][i];
	}
	long long den = 0;
	for (int i = 1; i <= n; ++i) {
		den += (n - i + 1) *1ll* (n - i + 1);
	}
	cout << setprecision(8) << fixed << 1.L * ans / den << endl;
	return 0;
}