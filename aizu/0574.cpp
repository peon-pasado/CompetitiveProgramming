#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
int a[maxn][maxn];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int x, y, l;
		cin >> x >> y >> l;
		a[x][y]++;
		a[x][y+1]--;
		a[x+l+1][y]--;
		a[x+l+2][y+1]++;
		a[x+l+1][y+l+2]++;
		a[x+l+2][y+l+2]--;
	}
	for (int i = 0; i < maxn; ++i)
		for (int j = 0; j < maxn; ++j)
			if (j > 0) a[i][j] += a[i][j-1];
	
	for (int i = 0; i < maxn; ++i)
		for (int j = 0; j < maxn; ++j)
			if (min(i, j) > 0) a[i][j] += a[i-1][j-1];
	
	for (int i = 0; i < maxn; ++i)
		for (int j = 0; j < maxn; ++j)
			if (i > 0) a[i][j] += a[i-1][j];
	
	int ans = 0;
	for (int i = 0; i < maxn; ++i)
		for (int j = 0; j < maxn; ++j)
			if (a[i][j] > 0) ans += 1;
	cout << ans << '\n';
	return 0;
}