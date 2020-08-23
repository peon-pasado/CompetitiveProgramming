/**
 * @author Miguel Mini
 * @tag dp, rerooting
 * @idea 
 *		- We must observe that if 
 *		we set the root as the start, 
 *		we can make a dp where the 
 *		rule is to take a node all 
 *		neighboring nodes that are 
 *		children must be taken, and 
 *		current node if choose a child 
 *		where it has been taken.
 * 
 *		- we can use rerooting technique 
 *		and fix every root.
 **/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int maxk = 101;
using ll = long long;
ll nei[maxn];
vector<int> g[maxn];
int a[maxn];
int k;

ll dp[maxn][maxk][2][2];
void add(int x, int k, int t, ll v) {
	if (dp[x][k][t][0] < v) {
		dp[x][k][t][1] = dp[x][k][t][0];
		dp[x][k][t][0] = v;
	} else {
		dp[x][k][t][1] = max(dp[x][k][t][1], v);
	}
}

const ll inf = 1e18;
void dfs(int x, int p) {
	nei[x] = 0;
	for (int v : g[x]) {
		if (v == p) continue;
		nei[x] += a[v];
	}
	for (int i = 0; i <= k; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int t = 0; t < 2; ++t) {
				dp[x][i][j][t] = -inf;
			}
		}	
	}
	add(x, 0, 0, 0);
	add(x, 1, 1, nei[x]);
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
		for (int i = 1; i <= k; ++i) {
			ll L = max(dp[v][i][0][0], dp[v][i][1][0]+a[x]);
			ll R = max(dp[v][i-1][0][0], dp[v][i-1][1][0]+a[x])+nei[x]-a[v];
			add(x, i, 0, L);
			add(x, i, 1, R);
		}
	}
}

void dfs_root(int x, int p) {
	if (p > 0) {
		ll calc[maxk][2];
		for (int i = 0; i <= k; ++i) {
			for (int t = 0; t < 2; ++t) {
				calc[i][t] = -inf;
			}
		}
		calc[0][0] = 0;
		calc[1][1] = dp[p][1][1][0] - a[x];
		for (int i = 1; i <= k; ++i) {
			if (dp[p][i][0][0] == max(dp[x][i][0][0], dp[x][i][1][0]+a[p])) {
				calc[i][0] = dp[p][i][0][1];
			} else {
				calc[i][0] = dp[p][i][0][0];
			}
			if (dp[p][i][1][0] == 
					max(dp[x][i-1][0][0], dp[x][i-1][1][0]+a[p])+nei[p]-a[x]) {
				calc[i][1] = dp[p][i][1][1]-a[x];	
			} else {
				calc[i][1] = dp[p][i][1][0]-a[x];
			}
		}
		nei[x] += a[p];
		for (int i = 1; i <= k; ++i) {
			dp[x][i][1][0] += a[p];
			dp[x][i][1][1] += a[p];
			ll fdp = max(calc[i][0], calc[i][1]+a[x]);
			ll sdp = max(calc[i-1][0], calc[i-1][1]+a[x])+nei[x]-a[p];
			add(x, i, 0, fdp);
			add(x, i, 1, sdp);
		}
	}
	for (int v : g[x]) {
		if (v == p) continue;	
		dfs_root(v, x);
	}
}

int main() {
	int n;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int root = 1;
	dfs(root, 0);
	dfs_root(root, 0);
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			res = max(res, max(dp[i][j][0][0], dp[i][j][1][0]));
		}
	}
	cout << res << endl;
	return 0;
}
