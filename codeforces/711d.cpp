#include <bits/stdc++.h>
using namespace std;
const int maxN = 2e5 + 10; 
int cnt[maxN];
bool vis[maxN];
int a[maxN];
vector<int> g[maxN], g2[maxN];
vector<int> topo;
int n;

void dfs(int x) {
	vis[x] = 1;
	for (int v : g[x]) {
		if (not vis[v]) {
			dfs(v);
		}
	}
	topo.push_back(x);
}

int color[maxN];
void dfs2(int x, int c) {
	vis[x] = 1;
	cnt[c] += 1;
	color[x] = c; 
	if (not vis[a[x]]) {
		dfs2(a[x], c);
	}	
}

const int mod = 1e9 + 7;
int add(int a, int b) {
	return (a+b)%mod;
}

int mul(long long a, long long b) {
	return a * b % mod;
} 

int pot[maxN];
int dfs3(int x) {
	vis[x] = 1;
	int ans = 1;
	for (int v : g2[x]) {
		if (not vis[v]) {
			ans = mul(ans, mul(2, dfs3(v)));
		}
	}
	return cnt[x] > 1 ? mul(ans, add(pot[cnt[x]], mod-2)) : ans;
}

int main() {
	pot[0] = 1;
	for (int i = 1; i < maxN; ++i) {
		pot[i] = add(pot[i-1], pot[i-1]);
	}
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		g[a[i]].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		if (not vis[i]) {
			dfs(i);
		}
	}
	int T = 0;
	reverse(begin(topo), end(topo));
	memset(vis, 0, sizeof vis);
	for (int v : topo) {
		if (not vis[v]) {
			dfs2(v, T++);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int v : g[i]) {
			if (color[i] != color[v]) {
				g2[color[i]].push_back(color[v]);
				g2[color[v]].push_back(color[i]);
			}
		}	
	}
	memset(vis, 0, sizeof vis);
	int ans = 1;
	for (int i = 0; i < T; ++i) {
		if (not vis[i]) {
			ans = mul(ans, dfs3(i));
		}
	}
	cout << ans << endl;
	return 0;
}