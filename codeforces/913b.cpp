#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
vector<int> g[maxN];
bool leaf[maxN];
int n;
bool ans = 1;

void dfs(int node) {
	leaf[node] = g[node].empty();
	int cnt = 0;
	for (int u : g[node]) {
		dfs(u);
		cnt += leaf[u];
	}
	if (not leaf[node]) {
		ans = ans and cnt >= 3;	
	}
}


int main() {
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		int p;
		cin >> p;
		g[p].emplace_back(i);
	}
	dfs(1);
	puts(ans ? "Yes" : "No");
	return 0;
}