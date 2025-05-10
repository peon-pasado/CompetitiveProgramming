#include <iostream>
#include <vector>
using namespace std;

const int maxn = 110;
const int inf = 1e9;
int dp[maxn][3];
vector<int> g[maxn];

int add(int a, int b) {
	return min(a+b, inf);
}

void update(int t[], int v) {
	if (v <= t[0]) {
		t[1] = t[0];
		t[0] = v;
	} else if (v < t[1]) {
		t[1] = v;
	}
}

void dfs(int x, int p) {
	int sum = 0;
	int best[2] = {100000, 100000};
	int one = 100000;
	for (int i = 0; i < g[x].size(); ++i) {
		int v = g[x][i];
		if (v == p) continue;
		dfs(v, x);
		sum = add(sum, dp[v][2]);
		update(best, min(dp[v][1], dp[v][0]) - dp[v][2]);
		one = min(one, dp[v][1] - dp[v][2]);
	}
	dp[x][0] = sum + 1;
	dp[x][2] = add(add(sum, best[0]), best[1]) - 1;
	dp[x][1] = add(sum, best[0]);
	dp[x][2] = min(dp[x][2], sum + one);
}

int main() {
	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for (int i = 0; i < n-1; ++i) {
			int a, b;
			cin >> a >> b;
			g[a].push_back(b);
			g[b].push_back(a);
		}
		dfs(1, 0);
		if (dp[1][2] < n) cout << dp[1][2] << '\n';
		else cout << -1 << '\n';
	}
	return 0;
}