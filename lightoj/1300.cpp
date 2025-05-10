#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <tuple>
#include <vector>
#include <numeric>
#define sz(c) ((int)c.size())
#define trav(it, c) for (auto it : c)
#define rep(var, begin, end) for (int var = begin; var < end; ++var)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()
#define compress(c) (sort(all(c)), c.erase(unique(all(c)), c.end()))
#define emb emplace_back
#define psb push_back
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
const int mod = 1e9 + 7;
const string file_base = "";

int add(int a, int b, int m = mod) {
    return a + b < m ? a + b : a + b - m;
}

int mul(ll a, ll b, int m = mod) {
    return a * b % m;
}

int ex(int a, int b, int m = mod) {
    int r=1;
    for (; b>0; b/=2, a=mul(a,a,m))
        if (b&1) r = mul(r, a, m);
    return r;
}

const int inf = 1.2e9;

vi num, st;
vector<vector<pii>> ed;
vector<int> bridge;
int Time;

int dfs(int at, int par) {
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
            top = min(top, num[y]);
            //if (num[y] < me)
            //    st.push_back(e);
        } else {
            int si = sz(st);
            int up = dfs(y, e);
            top = min(top, up);
            if (up == me) {
                //st.push_back(e);
                //st.resize(si);
            } else if (up < me) {
                //st.push_back(e);
            } else {
                bridge[e] = 1; 
                /* e is a bridge */
            }
        }
    }
    return top;
}

void bicomps() {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1);
    assert(st.empty());
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n, m;
        in >> n >> m;
        int eid = 0;
        ed.resize(n);
        rep(i, 0, n) 
            ed[i].clear();
        vector<pii> edges;
        rep(i, 0, m) {
            int a, b;
            in >> a >> b;
            ed[a].emb(b, eid);
            ed[b].emb(a, eid++);
        }
        bridge.assign(m, 0);
        bicomps();
        int cnt = 0, nodes;
        vector<bool> color(n), vis(n);
        function<bool(int, bool)> is_bipartite = [&](int x, bool c)->bool {
            nodes++;
            vis[x] = 1;
            color[x] = c;
            bool ans = 1;
            for (auto ed : ed[x]) {
                if (bridge[ed.second]) continue;
                if (!vis[ed.first]) ans &= is_bipartite(ed.first, c^1);
                else ans &= (c^1) == color[ed.first];
            }
            return ans;
        };
        rep(i, 0, n) {
            if (!vis[i]) {
                nodes=0;
                if (!is_bipartite(i, 0)) {
                    cnt += nodes;
                }
            }
        }
        out << cnt << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        in >> test_number;
        forn(tc, test_number) {
            out << "Case " << tc+1 << ": ";
            if (solve_one(in, out)) break;
        }
    }
};

int main() {
    Solver solver;
    if (!file_base.empty()) {
        ifstream in(file_base + ".in");
        ofstream out(file_base + ".out");
        in.exceptions(in.failbit);
        solver.solve(in, out);
    } else {
        cin.tie(nullptr)->sync_with_stdio(false);
        //cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}