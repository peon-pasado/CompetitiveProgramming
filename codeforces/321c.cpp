#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
int vis[maxN];
int sz[maxN];
char ans[maxN];
vector<int> g[maxN];
int n;

int centroid(int x, int n) {
	int mx = 0;
	vis[x] = 1;
	sz[x] = 1;
	int cen = -1;
	for (int v : g[x]) {
		if (not vis[v]) {
			cen = max(cen, centroid(v, n));
			sz[x] += sz[v];
			mx = max(mx, sz[v]);
		}
	}
	vis[x] = 0;
	mx = max(mx, n-sz[x]);
	if (2*mx <= n) return x;
	return cen;
}

void descomp(int x, int n, int ch) {
	int c = centroid(x, n);
	centroid(c, n);
	vis[c] = 2;
	ans[c] = ch;
	for (int v : g[c]) {
		if (not vis[v]) {
			descomp(v, sz[v], ch + 1);
		}	
	}
}


int main() {
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	descomp(1, n, 'A');
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << " \n"[i==n];
	}
	return 0;
}