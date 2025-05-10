#include <bits/stdc++.h>
using namespace std;
const int maxn = 302;
int c[maxn][maxn];
int dis[maxn][maxn];
bool vis[maxn];
int n;

using ii = pair<int, int>;
void dijkstra(int src) {
	memset(dis[src], 16, sizeof dis[src]);
	memset(vis, 0, sizeof vis);
	dis[src][src] = 0;
	for (int t = 0; t < n; ++t) {
		int x = -1, w = 2e9;
		for (int i = 0; i < n; ++i) {
			if (!vis[i]) {
				if (w >= dis[src][i]) {
					w = dis[src][i];
					x = i;
				}
			}	
		}
		vis[x] = 1;
		for (int i = 0; i < n; ++i) {
			if (!vis[i] && w + c[x][i] < dis[src][i]) {
				dis[src][i] = w + c[x][i];
			}
		}
	}
}

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", c[i]+j);
			}
		}
		for (int i = 0; i < n; i += n-1) {
			dijkstra(i);
		}
		int ans = dis[0][n-1];
		for (int i = 1; i < n-1; ++i) {
			for (int j = 1; j < n-1; ++j) {
				ans = min(ans, dis[0][i] 
								+ c[i][0] 
								+ c[j][n-1] 
								+ dis[n-1][j]);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}