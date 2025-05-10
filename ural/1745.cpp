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
const int maxn = 1010;
const int maxm = 10010;
int dp[maxn][maxm];
bool tr[maxn][maxm];

struct Bracket {
    int x, y;
    int n, id;
};

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int n;
        in >> n;
        vector<Bracket> v;
        for (int i = 0; i < n; ++i) {
            string s;
            in >> s;
            Bracket t = {0, 0, sz(s), i};
            for (int j = 0; j < s.size(); ++j) {
                //cout << s << endl;
                if (s[j] == '(') t.x++;
                if (s[j] == ')') {
                    if (t.x > 0) t.x--;
                    else t.y++;
                }
            }
            v.push_back(t);
        }
        sort(all(v), [](Bracket p, Bracket q)->bool {
            if (p.x > p.y && q.x > q.y) return p.y < q.y;
            if (p.x < p.y && q.x < q.y) return p.x > q.x;
            if (p.x == p.y && q.x == q.y) return p.x < q.x;
            if (p.x < p.y) return 0;
            if (p.x > p.y) return 1;
            if (q.x < q.y) return 1;
            if (q.x < q.y) return 0;
            return 0;
        });
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < maxm; ++j) {
                dp[i][j] = -inf;
            }
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            //cout << v[i-1].x << ' ' << v[i-1].y << '\n';
            for (int j = 0; j < maxm; ++j) {
                if (dp[i][j] < dp[i-1][j]) {
                    tr[i][j] = 0;
                    dp[i][j] = dp[i-1][j];
                }
                if (j >= v[i-1].y && j - v[i-1].y + v[i-1].x < maxm) {
                    int temp = dp[i-1][j] + v[i - 1].n;
                    //cout << "*" << j << ' ' << temp << '\n';
                    if (dp[i][j - v[i-1].y + v[i-1].x] < temp) {
                        tr[i][j - v[i-1].y + v[i-1].x] = 1;
                        dp[i][j - v[i-1].y + v[i-1].x] = temp;
                    }
                }
            }
            //for (int j = 0; j < 10; ++j) {
            //    cout << dp[i][j] << ' ';
            //}
            //cout << endl;
        }
        out << dp[n][0] << ' ';
        vector<int> ans;
        int temp = 0;
        for (int i = n; i >= 1; --i) {
            if (tr[i][temp]) {
                ans.push_back(v[i-1].id+1);
                temp += v[i-1].y - v[i-1].x;
            }
        }
        out << sz(ans) << '\n';
        reverse(all(ans));
        for (int i = 0; i < sz(ans); ++i) {
            out << ans[i] << ' ';
        }
        out << '\n';
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