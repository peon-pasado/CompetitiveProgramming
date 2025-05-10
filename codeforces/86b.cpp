#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e3 + 10;
char s[maxN][maxN];
int n, m;
const int maxM = maxN * maxN + 10;
int id[maxM];
int sz[maxM];
vector<int> g[maxM];

int val(int x, int y) {
	return x * maxN + y;
}

int get(int x) {
	return x != id[x] ? id[x] = get(id[x]) : x;
}

void Union(int x, int y) {
	x = get(x);
	y = get(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);	
	sz[x] += sz[y];	
	id[y] = x;
}
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
bool valid(int x, int y) {
	return min(x, y) >= 0 and x < n and y < m and s[x][y] != '#';
}

int color[maxM];
bool vis[maxM];

int main() {
	scanf("%d %d\n", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			id[val(i, j)] = val(i, j);
			sz[val(i, j)] = 1;
			s[i][j] = getchar();
		}
		getchar();
	}
	for (int d = 2; d <= 5; ++d)
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '#') continue;
			if (sz[get(val(i, j))] == 1) {	
				for (int k = 0; k < 4; ++k) {
					int ni = i + dx[k];
					int nj = j + dy[k];
					if (not valid(ni, nj)) continue;
					if (sz[get(val(ni, nj))] < d) {
						Union(val(i, j), val(ni, nj));
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '#') continue;
			if (sz[get(val(i, j))] == 1) return puts("-1"), 0;
			for (int k = 0; k < 4; ++k) {
				int ni = i + dx[k];
				int nj = j + dy[k];
				if (not valid(ni, nj)) continue;
				int u = get(val(i, j));
				int v = get(val(ni, nj));
				if (u != v) g[u].push_back(v);
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] != '#' and not vis[get(val(i, j))]) {
				int u = get(val(i, j));
				int mask = 0;
				vis[u] = 1;
				for (int v : g[u]) {
					if (vis[v]) mask |= 1<<color[v];  
				}
				mask ^= 1023;
				color[u] = 31 - __builtin_clz(mask & -mask);
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == '#') putchar('#');
			else printf("%d", color[get(val(i, j))]);
		}
		puts("");
	}
	return 0;
}