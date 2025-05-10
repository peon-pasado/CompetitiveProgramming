#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 10;
const int maxlog = 10 + 1;
int H[maxn];
int st[maxn][maxlog];
vector<int> g[maxn];

void dfs(int x, int p, int h) {
	H[x] = h;
	st[x][0] = p == 0 ? x : p;
	for (int k = 1; k < maxlog; ++k) {
		st[x][k] = st[st[x][k-1]][k-1];
	}
	for (int v : g[x]) {
		if (v == p) continue;	
		dfs(v, x, h+1);
	}
}

int jump(int x, int l) {
	for (int k = 0; k < maxlog; ++k) {
		if (l & (1<<k)) {
			x = st[x][k];
		}	
	}
	return x;
}

int lca(int x, int y) {
	if (H[x] > H[y]) swap(x, y);
	y = jump(y, H[y] - H[x]);
	if (x == y) return x;
	for (int k = maxlog-1; k >= 0; --k) {
		if (st[x][k] != st[y][k]) {
			x = st[x][k];
			y = st[y][k];
		}	
	}
	return st[x][0];
}

int dist(int x, int y) {
	return H[x] + H[y] - 2 * H[lca(x, y)];
}

int main() {
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; ++tc) {
		cout << "Case " << tc << ":\n";
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i) g[i].clear();
		for (int i = 1; i <= n; ++i) {
			int m;
			cin >> m;
			for (int j = 1; j <= m; ++j) {
				int x;
				cin >> x;
				g[i].push_back(x);
			}
		}
		dfs(1, 0, 0);
		int q;
		cin >> q;
		while (q--) {
			int a, b;
			cin >> a >> b;
			cout << lca(a, b) << endl;
		}
	}
	return 0;
}