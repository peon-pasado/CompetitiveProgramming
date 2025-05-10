#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int maxN = 105;
bool g[maxN][maxN];
bool g2[maxN][maxN];
bool vis[maxN];
int o[maxN], o2[maxN];
int h;
int in[maxN], out[maxN];
int col[maxN], col2[maxN];
int n;

void dfs(int x) {
	vis[x] = 1;
	for (int u = 1; u <= n; ++u) {
		if (not vis[u] and g[x][u]) { 
			dfs(u);
		}
	}
	o[h++] = x;
}

void dfs3(int x, int T) {
	vis[x] = 1;
	col2[x] = T;
	for (int u = 1; u <= n; ++u) {
		if (not vis[u] and (g2[x][u] or g2[u][x])) {
			dfs3(u, T);
		}
	}
}

void dfs2(int x, int c) {
	col[x] = c;
	vis[x] = 1;
	for (int u = 1; u <= n; ++u) {
		if (not vis[u] and g[u][x]) {
			dfs2(u, c);
		}
	} 
}


int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int w;
		while (scanf("%d", &w), w) g[i][w] = 1;	
	}
	for (int i = 1; i <= n; ++i) {
		if (not vis[i]) dfs(i);
	}
	for (int i = n-1; i >= 0; --i) {
		o2[i] = o[n-1-i];
	}
	int T = 0;
	for (int i = 0; i < maxN; ++i) vis[i] = 0;
	for (int i = 0; i < n; ++i) {
		if (not vis[o2[i]]) {
			dfs2(o2[i], T++);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (g[i][j] and col[i] != col[j])
				g2[col[i]][col[j]] = 1;
		}
	}
	int ans = 0;
	for (int i = 0; i < T; ++i) {
		int a = 0;
		for (int j = 0; j < T; ++j) {
			a += g2[j][i];
		}
		ans += a==0;
	}
	cout << ans << endl;
	if (T == 1) {
		return cout << 0 << endl, 0;
	}
	for (int i = 0; i < T; ++i) {
		int a = 0, b = 0;
		for (int j = 0; j < T; ++j) {
			a += g2[j][i];
			b += g2[i][j];
		}
		if (a == 0) in[col2[i]] += 1;
		if (b == 0) out[col2[i]] += 1;	
	}
	int ans2 = 0;
	for (int i = 0; i < T; ++i) {
		ans2 += max(in[i], out[i]);
	}
	cout << ans2 << endl;
	return 0;
}