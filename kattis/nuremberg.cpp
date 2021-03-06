/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dp on trees, rerooting, contribution technique
 * @idea 
 *    - use dp to sum edge contribution and rerooting.
 */

#include <bits/stdc++.h>
#define sz(x) (int)x.size()
#define trav(v, x) for (auto v : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define set_to(x, v) fill(all(x), v)
#define eb emplace_back
#define lso(x) ((x)&-(x))
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
const int mod = 1e9 + 7;
const int maxn = 5e4 + 10;
vector<ii> g[maxn];
int frec[maxn];
ll dp[maxn];
ll sz[maxn];

void dfs(int x, int p) {
    dp[x] = 0;
    sz[x] = frec[x];
    trav(v, g[x]) {
        if (v.first == p) continue;
        dfs(v.first, x);
        sz[x] += sz[v.first];
        dp[x] += v.second * sz[v.first] + dp[v.first];
    }
}

void dfs_reroot(int x, int p, int e) {
    if (p != 0) {
        ll temp = dp[p] - (e * sz[x] + dp[x]);
        dp[x] += e * (sz[p] - sz[x]) + temp;
        sz[x] = sz[p];
    }
    trav(v, g[x]) {
        if (v.first == p) continue;
        dfs_reroot(v.first, x, v.second);
    }
}

class MovingToNuremberg {
public:

    void solveOne(istream& in, ostream& out) {
        int n;
        in >> n;
        re(i, 1, n+1) {
            g[i].clear();
        }
        re(i, 1, n) {
            int a, b, t;
            in >> a >> b >> t;
            g[a].eb(b, t);
            g[b].eb(a, t);
        }
        int m;
        in >> m;
        memset(frec, 0, sizeof frec);
        re(i, 0, m) {
            int x, f;
            in >> x >> f;
            frec[x] = f;
        }
        dfs(1, 0);
        dfs_reroot(1, 0,0);
        ll t = *min_element(dp+1, dp+n+1);
        out << 2 * t << endl;
        re(i, 1, n+1) {
            if (dp[i] == t) {
                out << i << " \n"[i == n];
            }
        }
    }

    void solve(istream& in, ostream& out) {
        int testNumber = 1;
        in >> testNumber;
        re(tc, 1, testNumber+1) {
            //out << "Case #" << tc << ": ";
            solveOne(in, out);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    MovingToNuremberg solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}
