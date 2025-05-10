#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
const int mod = 1e9 + 9;
const int B = 143437;
using ll = long long;
int add(int a, int b) {
	return (a+b)%mod;
}
int mul(ll a, ll b) {
	return a*b%mod;
}
int H[maxn];
vector<int> g[maxn];
int st[maxn], en[maxn];
int T = 0;
int big[maxn];
int node[maxn];
int sz[maxn];
char c[maxn];
int h[maxn];

void dfs(int x, int p) {
	node[T] = x;
	st[x] = T++;
	sz[x] = 1;
	big[x] = -1;
	if (p >= 0) {
		H[x] = add(mul(H[p], B), c[x]);
		h[x] = h[p] + 1;
	} 
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
		sz[x] += sz[v];
		if (big[x] == -1 || sz[big[x]] < sz[v]) {
			big[x] = v;
		}
	}
	en[x] = T-1;
}

int need_hash = 0;
int b_pot = 0;
string need_s;

map<int, int> hash_set[maxn];
void add(int x) {
	hash_set[h[x]][H[x]]++;
}

void erase(int x) {
	hash_set[h[x]][H[x]]--;
}

ll ans = 0;
void dsu(int x, int p, bool keep) {
	for (int v : g[x]) {
		if (v == p || v == big[x]) continue;
		dsu(v, x, 0);
	}
	if (~big[x]) dsu(big[x], x, 1);
	add(x);
	for (int v : g[x]) {
		if (v == p || v == big[x]) continue;
		for (int i = st[v]; i <= en[v]; ++i) {
			add(node[i]);
		}
	}
	int t = need_s.size() - 1;
	if (c[x] == need_s[0] && h[x] + t < maxn) {
		ans += hash_set[h[x]+t][add(mul(H[x], b_pot), need_hash)];
	}
	if (!keep)
		for (int i = st[x]; i <= en[x]; ++i) {
			erase(node[i]);
		}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	int m = n;
	c[1] = '#'; 
	for (int i = 2; i <= n; ++i) {
		int pi;
		string s;
		cin >> pi >> s;
		for (int j = 0; j + 1 < s.size(); ++j) {
			g[pi].push_back(++m);
			c[m] = s[j];
			pi = m;
		}
		g[pi].push_back(i);	
		c[i] = s.back();
	}
	cin >> need_s;
	b_pot = 1;
	for (int i = 1; i < need_s.size(); ++i) {
		need_hash = add(mul(need_hash, B), need_s[i]);
		b_pot = mul(b_pot, B);
	}
	dfs(1, -1);
	dsu(1, -1, 1);
	cout << ans << '\n';
	return 0;
}