#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5 + 10;
struct Node {
	int x, y, id;
	bool operator<(Node q) const {
		return x *1ll* x + y *1ll* y < q.x *1ll* q.x + q.y *1ll* q.y;	
	}
	bool operator>(Node q) const {
		return x *1ll* x + y *1ll* y > q.x *1ll* q.x + q.y *1ll* q.y;	
	}
} p[maxN];
int n;
const long long inf  = 1500000;
bool o[maxN];
int id[maxN];
int sign[maxN];
vector<int> g[maxN];
int rnk[maxN];

int get(int x) {
	return x != id[x] ? id[x] = get(id[x]) : x;
}

void Union(int x, int y) {
	int u = get(abs(x));
	int v = get(abs(y));	
	if (u == v) return;
	if (rnk[u] < rnk[v]) {
		swap(u, v);
		swap(x, y);
	}
	id[v] = u;
	rnk[u] += rnk[u] == rnk[v];
	int sx = x >= 0 ? 1 : -1;
	int sy = y >= 0 ? 1 : -1;
	sign[u] *= sx;
	sign[v] *= sy;
	for (int e : g[v]) {
		g[u].push_back(sign[v] * sign[u] *  e);		
	}
}

bool check(long long x, long long y) {
	return x*x + y*y <= inf * inf;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		p[i] = {x, y, i};	
	}
	priority_queue<Node> Q;
	priority_queue<Node, vector<Node>, greater<Node>> Q2;

	for (int i = 1; i <= n; ++i) {
		Q.emplace(p[i]);
		Q2.emplace(p[i]);
		sign[i] = 1;
		g[i].push_back(i);
		id[i] = i;
	}
	while (Q.size() > 1) {	
		auto u = Q.top(); Q.pop();
		auto v = Q.top(); Q.pop();
		Node q = {u.x + v.x, u.y + v.y, -1};
		Node w = {u.x - v.x, u.y - v.y, -1};
		if (q < w) {
			Q.push(q);
		} else {						
			Q.push(w);
		}
	}
	while (Q2.size() > 1) {	
		auto u = Q2.top(); Q2.pop();
		auto v = Q2.top(); Q2.pop();
		Node q = {u.x + v.x, u.y + v.y, -1};
		Node w = {u.x - v.x, u.y - v.y, -1};
		if (q < w) {
			Q2.push(q);
		} else {						
			Q2.push(w);
		}
	}
	
	if (Q.top() < Q2.top()) {
		Q.pop();
		for (int i = 1; i <= n; ++i) Q.push(p[i]);
	while (Q.size() > 1) {
		auto u = Q.top(); Q.pop();
		auto v = Q.top(); Q.pop();
		Node q = {u.x + v.x, u.y + v.y, -1};
		Node w = {u.x - v.x, u.y - v.y, -1};
		if (q < w) {
			Union(u.id, v.id);
			q.id = get(u.id);
			Q.push(q);
		} else {						
			Union(u.id, -v.id);
			w.id = get(u.id);
			Q.push(w);
		}
	}
	} else {
		Q2.pop();
		for (int i = 1; i <= n; ++i) Q2.push(p[i]);
	while (Q2.size() > 1) {
		auto u = Q2.top(); Q2.pop();
		auto v = Q2.top(); Q2.pop();
		Node q = {u.x + v.x, u.y + v.y, -1};
		Node w = {u.x - v.x, u.y - v.y, -1};
		if (q < w) {
			Union(u.id, v.id);
			q.id = get(u.id);
			Q2.push(q);
		} else {						
			Union(u.id, -v.id);
			w.id = get(u.id);
			Q2.push(w);
		}
	}
		
	}

	int x = get(1);	
	for (int e : g[x]) {
		o[abs(e)] = e * sign[x] >= 0;
	}
	for (int i = 1; i <= n; ++i) cout << (o[i] ? "1 " : "-1 "); cout << endl;
	return 0;
}