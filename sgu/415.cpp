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
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
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
const int maxs = 210;
const int maxn = 1e4 + 10;
bool dpl[maxs][maxn], dpr[maxs][maxn];

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n, m;
        cin >> n >> m;
        vi a(n);
        trav(&x, a) in >> x;
        if (n == 1) {
            if (a[0] == m) {
                cout << 1 << '\n';
                cout << a[0] << '\n';
            } else {
                cout << 0 << '\n';
            }
            return 0;
        }
        dpl[0][0] = 1;
        dpl[0][a[0]] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= m; ++j) {
                dpl[i][j] = dpl[i][j] || dpl[i-1][j];
                if (j >= a[i]) 
                    dpl[i][j] = dpl[i][j] || dpl[i-1][j - a[i]];
            }
        }
        dpr[n-1][0] = 1;
        dpr[n-1][a[n-1]] = 1;
        for (int i = n-2; i >= 0; --i) {
            for (int j = 0; j <= m; ++j) {
                dpr[i][j] = dpr[i][j] || dpr[i + 1][j];
                if (j >= a[i])
                    dpr[i][j] = dpr[i][j] || dpr[i + 1][j - a[i]];
            }
        }
        vector<int> ans;
        if (!dpr[1][m]) ans.push_back(a[0]);
        if (!dpl[n-2][m]) ans.push_back(a[n-1]); 
        for (int i = 1; i+1 < n; ++i) {
            bool ok = 1;
            for (int j = 0; j <= m; ++j) {
                if (dpl[i-1][j] && dpr[i+1][m-j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) ans.push_back(a[i]);
        }
        sort(all(ans));
        cout << sz(ans) << '\n';
        for (int i = 0; i < sz(ans); ++i) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        //in >> test_number;
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
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