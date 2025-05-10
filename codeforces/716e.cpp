#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
using ll = long long;
int mod;

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(ll a, ll b) {
	return a*b%mod;
}

using ii = pair<int, int>; 
vector<ii> g[maxn];
int st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];

int f[maxn], k[maxn];
int ten_pot[maxn];
int inv_ten_pot[maxn];
int h[maxn];

void dfs(int x, int p, int d=0) {
	node[T] = x;
	st[x] = T++;
	sz[x] = 1;
	big[x] = -1;
	if (p >= 0) {
		h[x] = h[p] + 1;
		f[x] = add(mul(f[p], 10), d);
		k[x] = add(k[p], mul(d, ten_pot[h[p]]));
	}
	for (auto edge : g[x]) {
		int v = edge.first;
		int d = edge.second;
		if (v == p) continue;
		dfs(v, x, d);
		sz[x] += sz[v];
		if (big[x] == -1 || sz[big[x]] < sz[v]) {
			big[x] = v;
		}
	}
	f[x] = mul(f[x], inv_ten_pot[h[x]]);
	en[x] = T-1;
}

ll ans = 0;
map<int, int> cnt_f, cnt_k;
void update(int x) {
	cnt_f[f[x]]++;
	cnt_k[k[x]]++;
}

void query(int r, int x) {
	if (r != x) {
		int q = 0;
		q = add(k[r], mod - k[x]);
		q = mul(q, inv_ten_pot[h[r]]);
		q = mul(q, inv_ten_pot[h[r]]);
		q = add(q, f[r]);
		ans += cnt_f[q];
		
		q = add(f[r], mod - f[x]);
		q = mul(q, ten_pot[h[r]]);
		q = mul(q, ten_pot[h[r]]);
		q = add(q, k[r]);
		ans += cnt_k[q];
	} else {
		ans += cnt_f[f[x]];
		ans += cnt_k[k[x]];
	}
}

void erase(int x) {
	cnt_f[f[x]]--;
	cnt_k[k[x]]--;
}

void dsu(int x, int p, bool keep) {
	for (auto edge : g[x]) {
		int v = edge.first;
		if (v == p || v == big[x]) continue;
		dsu(v, x, 0);
	}
	if (~big[x]) dsu(big[x], x, 1);
	for (auto edge : g[x]) {
		int v = edge.first;
		if (v == p || v == big[x]) continue;
		for (int i = st[v]; i <= en[v]; ++i) {
			query(x, node[i]);
		}
		for (int i = st[v]; i <= en[v]; ++i) {
			update(node[i]);
		}
	}
	query(x, x);
	update(x);
	if (!keep)
		for (int i = st[x]; i <= en[x]; ++i) {
			erase(node[i]);
		}
}

int get_inv() {
	if (mod < 10) {
		for (int i = 1; i < mod; ++i) {
			if (10 * i % mod == 1) return i;
		}
	} else {
		for (int i = 1; i < 10; ++i) {
			if ((mod*1ll*i + 1) % 10 == 0) {
				return (mod*1ll*i + 1) / 10;
			}
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n >> mod;
	if (mod == 1) {
		cout << n *1ll* (n-1) << '\n';
		return 0;
	}
	ten_pot[0] = 1;
	for (int i = 1; i < maxn; ++i) {
		ten_pot[i] = mul(ten_pot[i-1], 10);
	}
	int inv_ten = get_inv();
	inv_ten_pot[0] = 1;
	for (int i = 1; i < maxn; ++i) {
		inv_ten_pot[i] = mul(inv_ten_pot[i-1], inv_ten);	
	}
	for (int i = 1; i <= n-1; ++i) {
		int u, v, d;
		cin >> u >> v >> d;
		g[u].push_back({v, d});
		g[v].push_back({u, d});
	}
	dfs(0, -1);
	dsu(0, -1, 1);
	cout << ans << '\n';
	return 0;
}