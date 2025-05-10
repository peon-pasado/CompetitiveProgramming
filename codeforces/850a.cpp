#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e3 + 10;
int n;
int a[maxN][6];
bool vis[maxN];

int main() {
	srand(time(0));
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= 5; ++j) {
			cin >> a[i][j];
		}
	}
	int m = 0;
	for (int i = 1; i <= n; ++i) {
		for (int k = 1; k <= 500; ++k) {
			int b = rand() % n + 1;
			int c = rand() % n + 1;
			if (b == c or b == i or c == i) continue;
			int sum = 0;
			for (int l = 1; l <= 5; ++l) {
				sum += (a[b][l] - a[i][l]) * (a[c][l] - a[i][l]);
			}
			if (sum > 0) {
				m += 1;
				vis[i] = 1;
				break;
			}
		}
	}
	cout << n-m << endl;
	for (int i = 1; i <= n; ++i) {
		if (not vis[i]) cout << i << " ";
	} cout << endl;
	return 0;
}