#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;

struct Node {
    Node* l;
    Node* r;
    int64_t val;
    int cnt;

    Node() {
        l = r = nullptr;
        val = cnt = 0;
    }
};
const int maxN = 2e5 + 10;
Node* roots[maxN];
int n, s, d;


void build(Node*& root, int l, int r) {
    if (l == r) {
        root->val = 0;
        root->cnt = 0;
        return;
    }
    int mi = (l + r) / 2;
    root->l = new Node();
    build(root->l, l, mi);
    root->r = new Node();
    build(root->r, mi+1, r);

    root->val = root->l->val + root->r->val;
    root->cnt = root->l->cnt + root->r->cnt;
}

void update(Node* rx, Node*& ry, int pos, int64_t v, int l, int r) {
    ry = new Node();
    ry->l = rx->l;
    ry->r = rx->r;
    ry->val = rx->val;
    ry->cnt = rx->cnt;

    if (l == r) {
        assert(ry->l == nullptr && rx->r == nullptr);
        ry->val = v;
        ry->cnt = 1;
        return;
    }

    int mi = (l + r) / 2;
    if (pos <= mi) update(rx->l, ry->l, pos, v, l, mi);
    else update(rx->r, ry->r, pos, v, mi+1, r);

    ry->val = ry->l->val + ry->r->val;
    ry->cnt = ry->l->cnt + ry->r->cnt;
}

int64_t query(Node* ry, int k) {
    if (ry->cnt <= k) return ry->val;//-1e18;
    if (ry->l->cnt == k) return ry->l->val;
    if (ry->l->cnt > k) return query(ry->l, k);
    return ry->l->val + query(ry->r, k - ry->l->cnt);
}


using lint = long long;
using llf = long double;
using pi = array<int, 2>;

// Let a matrix be monotone if Opt(i) <= Opt(i + 1) for all rows i.
// Given a totally monotone matrix (where every 2x2 submatrix is monotone), find the list of row optima positions.
// Need to implement select(r, u, v): checks if v is "better" solution than u.
// Ex) if we are finding a maximum, select(r, u, v) = (f(r, u) <= f(r, v)) since it makes v better.

template<class F>
bool select(int r, int u, int v, const F& f) {
	assert(u < v);
	return f(r, u) < f(r, v);
}

template<class F>
vector<int> recurse(vector<int> &rw, vector<int> &cl, const F& f) {
	if (sz(rw) == 1) {
		vector<int> opt = {0};
		for (int i = 1; i < sz(cl); i++) {
			if (select(rw[0], cl[opt[0]], cl[i], f))
				opt[0] = i;
		}
		return opt;
	}
	vector<int> stk, rev;
	for (int i = 0; i < sz(cl); i++) {
		while (sz(stk) && select(rw[sz(stk) - 1], stk.back(), cl[i], f)) {
			stk.pop_back();
			rev.pop_back();
		}
		if (sz(stk) < sz(rw)) {
			stk.push_back(cl[i]);
			rev.push_back(i);
		}
	}
	vector<int> half;
	for (int i = 0; i < sz(rw); i += 2) {
		half.push_back(rw[i]);
	}
	vector<int> ans(sz(rw));
	auto interp = recurse(half, stk, f);
	for (int i = 0; i < sz(interp); i++)
		ans[2 * i] = interp[i];
	for (int i = 1; i < sz(ans); i += 2) {
		int s = ans[i - 1];
		int e = (i + 1 < sz(ans) ? ans[i + 1] : sz(stk) - 1);
		ans[i] = s;
		for (int j = s + 1; j <= e; j++) {
			if (select(rw[i], stk[ans[i]], stk[j], f))
				ans[i] = j;
		}
	}
	for (int i = 0; i < sz(ans); i++)
		ans[i] = rev[ans[i]];
	return ans;
}

template<class F>
vector<int> smawk(int n, int m, F f) {
	assert(n >= 1 && m >= 1);
	vector<int> rw(n), cl(m);
	iota(all(rw), 0);
	iota(all(cl), 0);
	return recurse(rw, cl, f);
}

const int64_t inf = 1e18;
int64_t solve(int s, int d) {
    auto f1 = [&](int r, int c)->int64_t {
        r -= 2 * c;
        if (r < 0) return -inf; 
        if (r == 0 || c == 0) return 0LL;
        return query(roots[s - c], r);
    };
    auto r1 = smawk(d + 1, s + 1, f1);
    auto f2 = [&](int r, int c)->int64_t {
        r -= c;
        if (r < 0) return -inf;
        if (r == 0) return 0LL;
        return query(roots[s + c], r);
    };
    auto r2 = smawk(d + 1, n - s, f2); 
    int64_t res = -inf;
    for (int i=0; i<=d; ++i) {
        res = max(res, f1(i, r1[i]) + f2(d - i, r2[d - i]));
    }
    auto f3 = [&](int r, int c)->int64_t {
        r -= c;
        if (r < 0) return -inf; 
        if (r == 0 || c == 0) return 0LL;
        return query(roots[s - c], r);
    };        
    auto r3 = smawk(d + 1, s + 1, f3);
    auto f4 = [&](int r, int c)->int64_t {
        r -= 2 * c;
        if (r < 0) return -inf;
        if (r == 0) return 0LL;
        return query(roots[s + c], r);
    };
    auto r4 = smawk(d + 1, n - s, f4);
    for (int i=0; i<=d; ++i) {
        res = max(res, f3(i, r3[i]) + f4(d-i, r4[d-i]));
    }
    return res;
}


int main() {
    cin>>n>>s>>d;
    vector<int64_t> a(n);
    vector<pair<int64_t, int>> b(n);
    vector<int> pos(n);
    for (int i=0; i<n; ++i) {
        cin>>a[i];
        b[i] = make_pair(a[i], i);
    }
    sort(b.rbegin(), b.rend());
    for (int i=0; i<n; ++i) {
        pos[b[i].second] = i;
    }
    Node* r1 = new Node();
    Node* r2 = new Node(); 
    build(r1, 0, n-1);
    build(r2, 0, n-1);
    for (int i=s-1; i>=0; --i) {
        update(r1, roots[i], pos[i], a[i], 0, n-1);
        r1 = roots[i];
    }
    for (int i=s; i<n; ++i) {
        update(r2, roots[i], pos[i], a[i], 0, n-1);
        r2 = roots[i];
    }  
    cout << solve(s, d) << endl;
    return 0;
} 