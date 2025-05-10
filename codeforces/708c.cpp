#include <bits/stdc++.h>
using namespace std;
const int maxN = 4e5 + 10;
int sz[maxN];
int big[maxN];
vector<int> g[maxN];
vector<int> arr[maxN];
int n;

void init(int x) {
	sz[x] = 1;
	arr[x] = {0, 0};
	big[x] = 0;
}

void upd(int x, int v) {
	sz[x] += sz[v];
	arr[x].push_back(max(sz[v] * (2*sz[v] <= n), arr[v][0]));
	sort(rbegin(arr[x]), rend(arr[x]));
	arr[x].pop_back();
	big[x] = max(big[x], sz[v] - arr[v][0]);
}

void check(int x, int v) {
	int val = max(sz[x] * (2*sz[x] <= n), arr[x][0]);
	int val2 = sz[v] - sz[x];
	int val3 = (arr[v][0] == val ? arr[v][1] : arr[v][0]);
	big[x] = max(big[x], val2 - val3);
	sz[x] = n;
	arr[x].push_back(max(val2 * (2*val2 <= n), val3));
	sort(rbegin(arr[x]), rend(arr[x]));
	arr[x].pop_back();
}

void dfs(int x, int p=0) {
	init(x);
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
		upd(x, v);
	}
}

void dfs2(int x, int p=0) {
	if (p) {
		check(x, p);
	}
	for (int v : g[x]) {
		if (v == p) continue;
		dfs2(v, x);
	}
}


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	dfs2(1);
	for (int i = 1; i <= n; ++i) {
		cout << (2*big[i] <= n) << " \n"[i==n];
	}
	return 0;
}