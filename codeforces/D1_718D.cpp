/**
 * @author Miguel Mini
 * @tag dp_rerooting, hashing
 * @idea
 *      - we can hash every tree
 *      with hash of his subtrees.
 *  
 *      - we can force degree == 4.
 * 
 *      - we can simplify hashing
 *      to 4-degree and find hash
 *      to root.
 * 
 *      - we can solve for others
 *      nodes with a rerooting technique.
 * 
 * @complexity O(n \log n)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+9;
const int MAXN = 1e5 + 10;
const int p = 257;
const int q = 1e9+7;
multiset<int> H[MAXN];
vector<int> g[MAXN];
int n;
int cnt = 0;
map<multiset<int>, int> M;


int add(int a, int b) {
	return (a+b)%mod;
}

int mul(long long a, long long b) {
	return a*b%mod;
}

int hashing(const multiset<int> H) {
	if (not M.count(H)) 
		M[H] = cnt++;
	return M[H];
}

void dfs(int x, int p) {
	for (int v : g[x]) {
		if (v == p) continue;
		dfs(v, x);
		H[x].insert(hashing(H[v]));
	}
	for (int i = H[x].size(); i < 4; ++i) {
		H[x].insert(mod-1);
	}
}

set<int> Set;
void dfsRoot(int x, int p) {
	if (p) {
		multiset<int> aux = H[p];
		aux.erase(aux.lower_bound(hashing(H[x])));
		aux.insert(mod-1);
		H[x].erase(H[x].lower_bound(mod-1));
		H[x].insert(hashing(aux));
	}
	if (g[x].size() != 4)
		Set.insert(hashing(H[x]));
	for (int v : g[x])
		if (v != p)
			dfsRoot(v, x);
}


int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf ("%d %d",  &u, &v);
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}

	dfs(1, 0);
	dfsRoot(1, 0);
	cout << Set.size() << endl;

	return 0;
}