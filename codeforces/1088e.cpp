#include <bits/stdc++.h>
using namespace std;
const int maxN = 3e5 + 10;
vector<int> g[maxN];
int n;
int a[maxN];
long long dp[maxN];
long long best, k;
long long dfs(int x, int p = 0) {
	dp[x] = a[x];
	for (int v : g[x]) {
		if (v != p) {
			dp[x] += max(0ll, dfs(v, x));
		}
	}
	return dp[x];
}
long long dfs2(int x, int p = 0) {
	dp[x] = a[x];
	for (int v : g[x]) {
		if (v != p) {
			dp[x] += max(0ll, dfs2(v, x));
		}
	}
	return dp[x] == best ? (k+=1, 0) : dp[x];
}



int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a+i);
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int v = *max_element(a+1, a+n+1);
	if (v < 0) {
		int k = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i] == v) {
				k += 1;
			}
		}
		printf("%lld %d\n", k*1ll*v, k);
	} else {
		dfs(1);
		best = *max_element(dp+1, dp+n+1);
		dfs2(1);
		printf("%lld %d\n", k*best, k);
	}
	return 0;
}