#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int up[maxN][20];
int h[maxN];
long long sum[maxN];
vector<int> g[maxN];
int dp[maxN];
int a[maxN];
int n, L;
long long S;

void lca(int x, int p=0) {
	up[x][0] = p;
	for (int i = 1; i < 20; ++i) {
		up[x][i] = up[up[x][i-1]][i-1];
	}
	h[x] = h[p] + 1; 
	sum[x] = sum[p] + a[x];
	for (int v : g[x]) {
		if (v != p) {
			lca(v, x);
		}
	}
}

int get(int node) {
	int x = node;
	long long s = S;
	int l = 0;
	for (int i = 19; i >= 0; --i) {
		if (sum[x] - sum[up[x][i]] <= s and l + h[x] - h[up[x][i]] <= L) {
			s -= sum[x] - sum[up[x][i]];
			l += h[x] - h[up[x][i]];
			x = up[x][i];
		}
	}
	return h[x] + 1;
}

int dfs(int x, int p=0) {
	int nx = get(x);
	dp[x] = 0;
	int big = h[x] + 1;
	for (int v : g[x]) {
		if (v != p) {
			big = min(big, dfs(v, x));
			dp[x] += dp[v];
		}
	}
	if (big > h[x]) dp[x] += 1;
	else nx = big;
	return nx;
}


int main() {
	scanf("%d %d %lld", &n, &L, &S);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a+i);
	}
	for (int i = 2; i <= n; ++i) {
		int u;
		scanf("%d", &u);
		g[u].push_back(i);
		g[i].push_back(u);
	}
	if (*max_element(a+1, a+n+1) > S) return puts("-1"), 0;
	
	lca(1);
	dfs(1);
	printf("%d\n", dp[1]);
	return 0;
}