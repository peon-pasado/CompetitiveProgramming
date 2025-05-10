#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxN = 5e3 + 10;
bool vis[maxN];
int r[maxN];
int deg[maxN];
bool bridge[maxN][maxN];
vector<int> g[maxN];
int n, m;

bool visited[maxN];
int tin[maxN], low[maxN];
int timer;
int bb;

void dfsB(int v, int p = 0) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfsB(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
				bridge[to][v] = bridge[v][to] = 1;
			}
        }
    }
}

void find_bridges() {
	for (int i = 1; i <= n; ++i) {
		tin[i] = -1;
		low[i] = -1;
	}
    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            dfsB(i);
    }
}

void dfs3(int x, int c) {
	vis[x] = 1;
	r[x] = c;
	for (int i = 0; i < g[x].size(); ++i) {
		int v = g[x][i];
		if (not vis[v] and not bridge[x][v]) {
			dfs3(v, c);
		}
	}
}

int main() {
	cin >> n >> m;
	if (n == 1) {
		cout << max(0, 2-m) << endl;
		return 0;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	/*
	int components = 0;
	for (int i = 1; i <= n; ++i) {
		if (not vis[i]) {
			dfs(i);	
			components += 1;
		}
	}
	*/
	find_bridges();	
	int T = 0;	
	for (int i = 1; i <= n; ++i) {
		if (not vis[i]) {
			dfs3(i, T++);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i+1; j <= n; ++j) {
			if (bridge[i][j]) {
				deg[r[i]] += 1;
				deg[r[j]] += 1; 
			}
		}	
	}
	int ans = 0;
	for (int i = 0; i <= n; ++i) {
		ans += deg[i] == 1;
	}
	cout << (ans + 1)/2 << endl;
	return 0;
}