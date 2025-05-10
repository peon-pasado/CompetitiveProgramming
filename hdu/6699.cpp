#include <bits/stdc++.h>
using namespace std;

const int maxn = 2010;
bool vis[maxn][maxn];
int n, m;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool valid(int x, int y) {
	return min(x, y) >= 1 && x <= n && y <= m;
}

int dfs(int x, int y) {
	if (vis[x][y]) return 0;
	int sum[2] = {0};
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!valid(nx, ny)) continue;
		sum[i / 2] += vis[nx][ny];
	}
	if (sum[0] >= 1 && sum[1] >= 1) {
		vis[x][y] = 1;
		ans = 1;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!valid(nx, ny)) continue;
			ans += dfs(nx, ny);
		}
	}
	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int q;
		scanf("%d%d%d", &n, &m, &q);
		memset(vis, 0, sizeof vis);
		while (q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			int ans = 0;
			if (!vis[x][y]) {
				ans = 1;
				vis[x][y] = 1;
				for (int i = 0; i < 4; ++i) {
					int nx = x + dx[i];
					int ny = y + dy[i];
					if (!vis[nx][ny]) ans += dfs(nx, ny);
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}