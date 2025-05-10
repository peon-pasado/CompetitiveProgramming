#include <iostream>
#include <vector>
using namespace std;
const int inf = 1e9;
const int maxn = 1010;
vector<pair<int, int> > g[maxn];
int dis[maxn][maxn];
int cover[maxn][maxn];
int memo[maxn];
int w[maxn];
int d[maxn];
int t, n;

void calc_dist(int x, int root, int p, int h) {
	dis[root][x] = h;
	for (int i = 0; i < g[x].size(); ++i) {
		pair<int, int> u = g[x][i];
		if (u.first == p) continue;
		calc_dist(u.first, root, x, h + u.second);
	}
}

int dp(int x, int p) {
	calc_dist(x, x, 0, 0);
	for (int j = 1; j <= n; ++j) {
		if (dis[x][j] <= d[x]) {
			cover[x][j] = w[j];
		} else {
			cover[x][j] = inf;
		}
	}
	memo[x] = inf;
	for (int i = 0; i < g[x].size(); ++i) {
		pair<int, int> u = g[x][i];
		if (u.first == p) continue;
		dp(u.first, x);
		for (int j = 1; j <= n; ++j) {
			if (dis[x][j] > d[x]) continue;
			cover[x][j] += min(memo[u.first], cover[u.first][j] - w[j]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		memo[x] = min(memo[x], cover[x][i]);
	}
	return memo[x];
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for (int i = 1; i <= n; ++i) {
			cin >> w[i];
		}
		for (int i = 1; i <= n; ++i) {
			cin >> d[i];
		}
		for (int i = 1; i < n; ++i) {
			int a, b, c;
			cin >> a >> b >> c;
			g[a].push_back(make_pair(b, c));
			g[b].push_back(make_pair(a, c));
		}
		cout << dp(1, 0) << endl;
	}
	return 0;
}