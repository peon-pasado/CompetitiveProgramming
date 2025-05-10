#include <bits/stdc++.h>
using namespace std;
const int maxN = 301;
int memo[maxN][maxN][maxN];
bool vis[maxN][maxN][maxN];
int n;
int a[maxN][maxN];
int dp(int x, int y, int d) {
	if (d < 0) {
		x += d;
		y -= d;
		d *= -1;
	}
	if (min(x, y) <= 0 or min(x+d, y-d) <= 0) return -1e9;
	if (x > n or y > n or x + d > n or y - d > n) return -1e9;
	if (x == n and y == n) return a[x][y];
	if (vis[x][y][d]) return memo[x][y][d];
	int temp = a[x][y] + (d!=0 ? a[x+d][y-d] : 0);
	int &ans = memo[x][y][d] = -1e9;
	for (int i = 0; i < 4; ++i) {
		int m1 = i&1;
		int m2 = (i>>1)&1;
		ans = max(ans, temp + dp(x+m1, y+1-m1, d+m2-m1));
	}
	vis[x][y][d] = 1;
	return ans;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> a[i][j];
		}
	}
	cout << dp(1, 1, 0) << endl;
	return 0;
}