#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi num;
vector<vector<pii>> ed;
vector<int> w;

int Time;

int dfs(int at, int par) {
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
            top = min(top, num[y]);
            // if (num[y] < me)
            //	st.push_back(e);
        } else {
            // int si = sz(st);
            int up = dfs(y, e);
            top = min(top, up);
            if (up == me) {
                // st.push_back(e);
                // f(vi(st.begin() + si, st.end()));
                // st.resize(si);
            } else if (up < me) {
                // st.push_back(e);
            } else {
                /* e is a bridge */
                w[e] = 1;
            }
        }
    }
    return top;
}

void bicomps() {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1);
}

vector<vector<pii>> T;
vi color;
void dfs_(int x, int c) {
    color[x] = c;
    for (auto e : ed[x]) {
        if (color[e.first] != -1)
            continue;
        if (w[e.second])
            continue;
        dfs_(e.first, c);
    }
}

const int maxn = 1e5 + 10;
int h[maxn];
int st[maxn][17];
int L[maxn], R[maxn];
int TT = 0;

void dfs_st(int x, int p) {
    L[x] = TT++;
    h[x] = p==-1?0:h[p]+1;
    st[x][0] = p==-1?x:p;
    for (int i = 1; i < 17; ++i) {
        st[x][i] = st[st[x][i-1]][i-1];
    }
    for (auto e : T[x]) {
        if (e.first == p) continue;
        dfs_st(e.first, x);
    }
    R[x] = TT++;
}

int lca(int x, int y) {
    if (h[x]>=h[y]) swap(x, y);
    for (int i = 16; i>=0; --i) {
        if (h[st[y][i]] >= h[x]) {
            y=st[y][i];
        }
    }
    if (x==y) return x;
    for (int i = 16; i>=0; --i) {
        if (st[x][i]!=st[y][i]) {
            x=st[x][i];
            y=st[y][i];
        }
    }
    return st[x][0];
}

bool is_parent(int a, int b) {
    return L[a] <= L[b] && R[b] <= R[a];
}

int inter(int a, int b, int c, int d) {
    if (is_parent(a, c) || is_parent(c, a)) {
        if (h[a] > h[c]) {
            return h[lca(b, d)] - h[lca(a, d)]; 
        } else {
            return h[lca(d, b)] - h[lca(c, b)];
        }
    } 
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    ed.assign(n, vector<pii>());
    w.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ed[a].emplace_back(b, i);
        ed[b].emplace_back(a, i);
    }
    bicomps();
    T.assign(n, vector<pii>());
    color.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            dfs_(i, i);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto e : ed[i]) {
            if (w[e.second]) {
                T[color[i]].emplace_back(color[e.first], e.second);
            }
        }
    }
    dfs_st(0, -1);
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        a = color[a];
        b = color[b];
        c = color[c];
        d = color[d];
        int e = lca(c, d);
        int dis = h[c] + h[d] - 2 * h[e];
        int f = lca(a, b);
        dis -= inter(e, c, f, a) + inter(e, d, f, b) + inter(e, c, f, b) + inter(e, d, f, a);
        cout << dis << '\n';
    }
    return 0;
}
