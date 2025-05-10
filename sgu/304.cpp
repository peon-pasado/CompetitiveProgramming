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
int n, k, p;
const int maxn = 610;
vector<ii> d[maxn];
int dp[maxn][maxn];
int tr[maxn][maxn];

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        in >> n >> k >> p; 
        vector<int> b(k);
        for (int i = 0; i < k; ++i) {
            in >> b[i];
        }
        for (int i = 0; i < n; ++i) {
            int x, y;
            in >> x >> y;
            d[y].push_back({x, i+1});
        }
        for (int i = 1; i <= k; ++i) {
            sort(all(d[i]));
            for (int t = 1; t < d[i].size(); ++t) {
                d[i][t].first += d[i][t-1].first;
            }
        }
        for (int j = 1; j <= n; ++j)
            for (int i = 0; i <= k; ++i) 
                dp[i][j] = inf;
        dp[0][0] = 0;
        for (int i = 1; i <= k; ++i) {
            for (int m = 1; m <= n; ++m) {
                dp[i][m] = dp[i-1][m];
                tr[i][m] = 0;
                for (int t = 0; t < d[i].size(); ++t) {
                    if (m - t - 1 < 0) break;
                    int temp = dp[i - 1][m - t - 1] + b[i - 1] + d[i][t].first;
                    if (dp[i][m] > temp) {
                        dp[i][m] = temp;
                        tr[i][m] = t + 1;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (dp[k][i] <= p) ans = i;
        }
        cout << ans << '\n';
        vector<int> res;
        for (int i = k; i >= 1; --i) {
            int t = tr[i][ans];
            for (int j = 0; j < t; ++j) {
                res.push_back(d[i][j].second);
            }
            ans -= t;
        }
        sort(all(res));
        for (int i = 0; i < res.size(); ++i) {
            cout << res[i] << ' ';
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