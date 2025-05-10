#include <bits/stdc++.h>
using namespace std;
const int maxN = 3e5 + 10;
bool vis[maxN];
int memo[maxN];
vector<int> g[maxN];
int n, m;
int e[maxN];

int dfs(int x) {
	if (vis[x]) return memo[x];
	vis[x] = 1;
	for (int v : g[x]) {
		dfs(v);
	}
	memo[x] = e[x];
	for (int v : g[x]) {
		memo[x] = max(
				memo[x], 
				(e[x] > e[v]) + memo[v])
			;
	} 
	return memo[x];
}


int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%d", e+i);
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[v].emplace_back(u);
	}
	for (int i = 0; i < n; ++i) {
		if (not vis[i]) {
			dfs(i);
		}
	}	
	printf("%d\n", *max_element(memo, memo+n));
	return 0;
}