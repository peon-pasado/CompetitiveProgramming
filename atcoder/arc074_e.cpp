/**
 * @author Miguel Mini
 * @tag dp, amortized
 * @idea
 *      - we can considere the
 *      next dp:
 * 
 *      dp(position, pos_r, pos_g, pos_b)
 * 
 *      where positions is current processed
 *      position ans pos_x is the more
 *      recent positions of color x.
 * 
 *      - note that:
 *           position = max(pos_r, pos_g, pos_b)
 * 
 * @complexity O(n^3)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 310;
const int mod = 1e9 + 7;
bool vis[maxn][maxn][maxn];
int memo[maxn][maxn][maxn];
vector<pair<int, int>> adj[maxn];
int n;
bool solve(int pos, int r, int g, int b) {
	for (auto e : adj[pos]) {
		int sum = 0;
		sum += r >= e.first;
		sum += g >= e.first;
		sum += b >= e.first;
		if (sum != e.second) return 0;
	}
	return 1;
}

int dp(int pos, int r, int g, int b) {
	if (pos == n+1) return 1;
	if (vis[r][g][b]) return memo[r][g][b];
	vis[r][g][b] = 1;
	int& ans = memo[r][g][b] = 0;
	if (solve(pos, pos, g, b)) {
		ans += dp(pos+1, pos, g, b);	
	}
	if (ans >= mod) ans -= mod;
	if (solve(pos, r, pos, b)) {
		ans += dp(pos+1, r, pos, b);
	}
	if (ans >= mod) ans -= mod;
	if (solve(pos, r, g, pos)) {
		ans += dp(pos+1, r, g, pos);
	}
	if (ans >= mod) ans -= mod;
	return ans;
}

int main() {
	int m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int l, r, x;
		cin >> l >> r >> x;
		adj[r].push_back({l, x});
	}
	cout << dp(1, 0, 0, 0) << '\n';
	return 0;
}