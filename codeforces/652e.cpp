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

int add(int a, int b, int m = mod)
{
    return a + b < m ? a + b : a + b - m;
}

int mul(ll a, ll b, int m = mod)
{
    return a * b % m;
}

int ex(int a, int b, int m = mod)
{
    int r = 1;
    for (; b > 0; b /= 2, a = mul(a, a, m))
        if (b & 1)
            r = mul(r, a, m);
    return r;
}

const int inf = 1.2e9;

vi num, st;
vector<vector<pii>> ed;
vector<bool> bridge;
vector<int> w;
vector<int> color;
int Time;

template <class F>
int dfs(int at, int par, F &f) {
    int me = num[at] = ++Time, e, y, top = me;
    trav(pa, ed[at]) if (pa.second != par) {
        tie(y, e) = pa;
        if (num[y]) {
            top = min(top, num[y]);
            if (num[y] < me)
                st.push_back(e);
        } else {
            int si = sz(st);
            int up = dfs(y, e, f);
            top = min(top, up);
            if (up == me) {
                st.push_back(e);
                f(vi(st.begin() + si, st.end()));
                st.resize(si);
            } else if (up < me) {
                st.push_back(e);
            } else {
                bridge[e] = 1;
                /* e is a bridge */
            }
        }
    }
    return top;
}

template <class F>
void bicomps(F f) {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}

vector<bool> vis;
int dfs_(int x, int pe = -1) {
    if (pe >= 0) vis[pe] = 1;
    int ans = 0;
    for (auto e : ed[x]) {
        if (bridge[e.second]) continue;
        if (vis[e.second]) continue;
        ans |= dfs_(e.first, e.second) || w[e.second];
    }
    return ans;
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n, m;
        in >> n >> m;
        ed.assign(n, vector<pii>());
        w.assign(m + 1, 0);
        color.assign(m + 1, 0);
        bridge.assign(m + 1, 0);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            in >> a >> b >> c;
            a--; b--;
            w[i] = c;
            ed[a].emplace_back(b, i);
            ed[b].emplace_back(a, i);
        }
        int x, y;
        cin >> x >> y;
        x--; y--;
        ed[x].emplace_back(y, m);
        ed[y].emplace_back(x, m);
        w[m] = 0;
        vis.assign(m + 1, 0);
        auto f = [&](vi x) {
            return;
        };
        bicomps(f);
        if (dfs_(x)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        //in >> test_number;
        forn(tc, test_number) {
            //out << "Case " << tc + 1 << ": ";
            if (solve_one(in, out))
                break;
        }
    }
};

int main()
{
    Solver solver;
    if (!file_base.empty()) {
        ifstream in(file_base + ".in");
        ofstream out(file_base + ".out");
        in.exceptions(in.failbit);
        solver.solve(in, out);
    }
    else
    {
        cin.tie(nullptr)->sync_with_stdio(false);
        // cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}