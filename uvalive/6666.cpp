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

struct Solver {
    bool solve_one(istream &in, ostream &out) {
        int m, n, s, w;
        in >> m >> n >> s >> w;
        if ((n+m+s+w) == 0) return 1;
        vector<vi> p;
        forn(i, m) {
            vi q(3);
            forn(j, 3) in >> q[j];
            p.emb(q);
        }
        int g = s;
        forn(i, n) {
            vi q(3);
            q[0] = (g/7) % 100 + 1;
            q[1] = (g/700) % 100 + 1;
            q[2] = (g/70000) % 100 + 1;
            p.emb(q);
            if (g % 2 == 0) g /= 2;
            else g = (g/2) ^ w; 
        }
        sort(all(p), [](vi a, vi b) {
            int na = a[0]*a[0] + a[1]*a[1] + a[2]*a[2];
            int nb = b[0]*b[0] + b[1]*b[1] + b[2]*b[2];
            return 1ll * a[0] * a[0] * nb  < 1ll * b[0] * b[0] * na;
         });
        auto norm = [](vi p) {
            return sqrtl(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
        };
        double min_dist = 1e20;
        vector<vi> best(2);
        forn(i, sz(p)) {
            rep(j, i+1, sz(p)) {
                double nj = norm(p[j]);
                double ni = norm(p[i]);
                if (p[j][0] / nj - p[i][0] / ni > min_dist) break;
                vector<double> q(3);
                forn(k, 3) q[k] = p[j][k] / nj - p[i][k]  / ni;
                double dist = sqrtl(q[0]*q[0] + q[1]*q[1] + q[2]*q[2]);
                if (dist < 1e-10) continue;
                auto a = p[j];
                auto b = p[i];
                if (a > b) swap(a, b);
                if (dist + 1e-10 < min_dist) {
                    best = {a, b};
                    min_dist = dist;
                } else if (dist < min_dist + 1e-10) {
                    if (a < best[0] || (best[0] == a && b < best[1])) {
                        best[0] = a;
                        best[1] = b;
                    }
                }
            }
        }
        out << best[0][0] << ' ' << best[0][1] << ' ' << best[0][2] << ' ';
        out << best[1][0] << ' ' << best[1][1] << ' ' << best[1][2] << '\n';
        return 0;
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1e9;
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