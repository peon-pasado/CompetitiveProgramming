#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 10;
int H[MAXN];
int st[MAXN][15];
int Max[MAXN][15];
int sz[MAXN];
struct Node {
	int v, w, id;
};
int A[MAXN*10], B[10*MAXN];
int t, n, m;
vector<Node>  g[MAXN];
int dfs(int x, int p = 0, int w = 0, int h = 0) {
	H[x] = h;
	st[x][0] = p == 0 ? x : p;
	Max[x][0] = w;
	sz[x] = 1;
	for (int i = 1; i <= 14; ++i) {
		st[x][i] = st[st[x][i-1]][i-1];
		Max[x][i] = max(Max[x][i-1], Max[st[x][i-1]][i-1]);
	}
	for (auto node : g[x])
		if (node.v != p) dfs(node.v, x, node.w, h+1), sz[x] += sz[node.v];
}
int walk(int x, int d) {
	for (int i = 0; i <= 14; ++i)
		if (d&(1<<i)) x = st[x][i];
	return x;
}
int getLCA(int u, int v) {
	if (H[u] > H[v]) swap(u, v);
	v = walk(v, H[v] - H[u]);
	if (v == u) return u;
	for (int i = 14; i >= 0; --i) {
		if (st[u][i] != st[v][i]) {
			u = st[u][i];
			v = st[v][i];
		}
	}
	return st[u][0];
}
int getMax(int u, int len) {
	int ans = 0;
	for (int i = 0; i <= 14; ++i) {
		if (len&(1<<i)) {
			ans = max(ans, Max[u][i]);
			u = st[u][i];		
		}
	}
	return ans;
}

multiset<int> Set[MAXN];
vector<int> in[MAXN], out[MAXN];

void dsu(int x, int p, int w, int id) {

	int big = -1, mx = -1;
	for (auto node : g[x]) {
		if (node.v != p) {
			dsu(node.v, x, node.w, node.id);
			if (mx < (int)Set[node.v].size()) {
				mx = Set[node.v].size();
				big = node.v;
			}
		}
	}

	Set[x].clear();
	if (big != -1) {
		swap(Set[x], Set[big]);
		for (auto node : g[x])
			if (node.v != p and node.v != big) {
				for (int s : Set[node.v]) {
					Set[x].insert(s);
				}
			}
	}

	for (int s : in[x]) 
		Set[x].insert(s);
		
	for (int s : out[x])
		Set[x].erase(Set[x].lower_bound(s));

	if (p) {
		if (not Set[x].empty()) A[id] += *(Set[x].begin()); 
		else A[id] = -1;
	}
	
	
}

int main() {
	scanf("%d", &t);
	int nc = 1;
	while (t--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for (int i = 1; i < n; ++i) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);	
			g[u].push_back({v, c, i});
			g[v].push_back({u, c, i});
			
			A[i] = -c;
			B[i] = -1;
		}
		dfs(1);

		for (int i = 1; i <= n; ++i){
			in[i].clear();
			out[i].clear();
		}
		
		for (int i = n; i <= m; ++i) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			int lca = getLCA(u, v);

			in[v].push_back(c);
			out[lca].push_back(c);
			in[u].push_back(c);
			out[lca].push_back(c);

			A[i] = -1;
			B[i] = c - max(getMax(u, H[u] - H[lca]), getMax(v, H[v] - H[lca]));
		}
		
		dsu(1, 0, 0, 0);

		long long ans = 0;
		for (int i = 1; i <= m; ++i) {
			ans += i * A[i] + i * 1ll * i * B[i];
		}
		printf("Case %d: %lld\n", nc++, ans);
	}
	return 0;
}