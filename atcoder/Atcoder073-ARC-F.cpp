/**
 * @author Miguel Mini
 * @tag segment_tree, lazy_propagation
 * @idea
 *      - we can maintain last
 *      positions with respective 
 *      contribution if the other 
 *      position is at p[i] (not counting p[i]).
 *      
 *      - asuming p[0] = B     
 * 
 *      - if we process p[i+1] we need
 *      answer of maintain position
 *      with cost |p[i] - p[i+1]| or
 *      from posittions [0, ..., i-1]
 *      move to position i, this is
 *      min(ans[j] + |p[i+1] - p[j]|)
 * 
 *      - we can maintain a ordered
 *      set and save answer, asnwer + p[j]
 *      and answer - p[j].
 * 
 * @complezity O(q \log q)
 */ 

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<pair<int, int>> o;

const int maxn = 2e5 + 10;
const ll inf = 1e18;
struct Node {
	ll x, l, r;
	Node(ll x=inf, ll l=inf, ll r=inf): x(x), l(l), r(r) {}
} st[maxn << 2];
ll lazy[maxn << 2];

Node merge(Node p, Node q) {
	return {
		min(p.x, q.x),
		min(p.l, q.l),
		min(p.r, q.r)
	};
}

void update_one(int x, ll val) {
	lazy[x] += val;
	st[x].x += val;
	st[x].l += val;
	st[x].r += val;
}

void push(int x) {
	if (lazy[x]) {
		update_one(x<<1, lazy[x]);
		update_one(x<<1|1, lazy[x]);
		lazy[x] = 0;
	}
}

void update(int pos, ll v, int nx=1, int l=0, int r=o.size()-1) {
	if (pos < l || pos > r) return;
	if (l == r) {
		st[nx] = {v, v-o[pos].first, v+o[pos].first};
		return;
	}
	int mid = (l+r)/2;
	push(nx);
	update(pos, v, nx<<1, l, mid);
	update(pos, v, nx<<1|1, mid+1, r);
	st[nx] = merge(st[nx<<1], st[nx<<1|1]);
}

void update_all(int l1, int r1, ll v, int nx=1, int l=0, int r=o.size()-1) {
	if (r1 < l || r < l1) return;
	if (l1 <= l && r <= r1) {
		update_one(nx, v);
		return;
	}
	int mid = (l+r)/2;
	push(nx);
	update_all(l1, r1, v, nx<<1, l, mid);
	update_all(l1, r1, v, nx<<1|1, mid+1, r);
	st[nx] = merge(st[nx<<1], st[nx<<1|1]);
}

Node query(int l1, int r1, int nx=1, int l=0, int r=o.size()-1) {
	if (r1 < l || r < l1) return Node();
	if (l1 <= l && r <= r1) return st[nx];
	int mid = (l + r) / 2;
	push(nx);
	return merge(query(l1, r1, nx<<1, l, mid), query(l1, r1, nx<<1|1, mid+1, r));
}

void add(pair<int, int> x, ll val) {
	int pos = lower_bound(o.begin(), o.end(), x) - o.begin();
	update(pos, val);
}

void add_all(ll val) {
	update_all(0, o.size()-1, val);
}

void init(vector<int>& p, int x) {
	o.push_back({x, 0});
	for (int i = 0; i < p.size(); ++i) {
		o.push_back({p[i], i+1});
	}
	sort(o.begin(), o.end());
	for (int i = 0; i <= 4*o.size(); ++i) {
		st[i] = Node();
	}
	add({x, 0}, 0);
}

ll get(int p) {
	int pos = lower_bound(o.begin(), o.end(), make_pair(p, -1)) - o.begin();
	auto L = query(0, pos);
	auto R = query(pos, o.size()-1);
	return min(L.l + p, R.r - p);
}

int main() {
	int n, q, A, B;
	cin >> n >> q >> A >> B;
	vector<int> p(q + 1);
	p[0] = B;
	for (int i = 1; i <= q; ++i) {
		cin >> p[i];
	}
	init(p, A);
	for (int i = 1; i <= q; ++i) {
		int delta = abs(p[i] - p[i-1]);
		add({p[i-1], i}, get(p[i]) - delta);
		add_all(delta);
	}
	cout << st[1].x << '\n';
	return 0;
}