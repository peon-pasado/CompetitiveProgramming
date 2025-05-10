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
const int maxn = 15;
int dist[maxn][maxn][2][2];
int get_dist(string& l, string& r) {
    for (int i = sz(l); i >= 0; --i) {
        bool ok = 1;
        for (int j = 0; j < min(sz(r), i); ++j) {
            if (r[j] != l[sz(l) - i + j]) {
                ok = 0;
                break;
            }
        }
        if (ok) return max(0, sz(r) - i);
    }
    return 0;
}

int memo[1<<14][15][2];
ii tr[1<<14][15][2];
bool vis[1<<14][15][2];
int n;

int dp(int mask, int last, int b) {
    if (mask == (1<<n)-1) return 0;
    if (vis[mask][last][b]) return memo[mask][last][b];
    vis[mask][last][b] = 1;
    int& ans = memo[mask][last][b] = 1e9;
    for (int i = 0; i < n; ++i) {
        if (mask&(1<<i)) continue;
        for (int d = 0; d < 2; ++d) {
            int w = 2 * dist[last][i][b][d];
            int temp = dp(mask | (1<<i), w == 0 ? last : i, w == 0 ? b : d) + 2 * dist[last][i][b][d];
            if (temp < ans) {
                tr[mask][last][b] = {i, d};
                ans = temp;
            }
        }
    }
    return ans;
}

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        in >> n;
        vector<string> s(n);
        trav(&x, s) in >> x;


        forn(i, n) forn(j, n)
            forn(k, 2) forn(l, 2) {
                string u = s[i], v = s[j];
                if (l == 0) reverse(all(v));
                if (k == 0) reverse(all(u)); 
                dist[i][j][k][l] = get_dist(u, v);
            }
        int best = 1e9, bi = 0, bb = 0;
        string ans;
        for (int i = 0; i < n; ++i) {
            string ri = s[i];
            reverse(all(ri));
            int wir = get_dist(s[i], ri);
            int wri = get_dist(ri, s[i]);
            //cout << wir << " " << wri << '\n';
            int ansl = dp(1<<i, i, 0) + sz(s[i]) + wir;
            int ansr = dp(1<<i, i, 1) + sz(ri) + wri;
            //cout << ansl << ' ' << ansr << '\n';
            if (best > min(ansl, ansr)) {
                best = min(ansl, ansr);
                bi = i;
                bb = ansr <= ansl;
                if (bb) {
                    ans = ri;
                    for (int j = 0; j < wri; ++j) {
                        ans += s[i][sz(s[i]) - wri + j];
                    }
                } else {
                    ans = s[i];
                    for (int j = 0; j < wir; ++j) {
                        ans += ri[sz(ri) - wir + j];
                    }
                }
            }
        }
        int mask = 1<<bi, last = bi, b = bb;
        for (int i = 1; i < n; ++i) {
            int ni = tr[mask][last][b].first;
            int nb = tr[mask][last][b].second;
            int len = dist[last][ni][b][nb];
            if (len > 0) {
                if (nb) {
                    string R = s[ni].substr(sz(s[ni]) - len, len);
                    string L = R;
                    reverse(all(L));
                    ans = L + ans + R;
                } else {
                    string L = s[ni].substr(0, len);
                    string R = L;
                    reverse(all(R));
                    ans = L + ans + R;
                }
            }
            mask |= (1<<ni);
            if (len > 0) last = ni, b = nb;
        }
        out << ans << '\n';
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