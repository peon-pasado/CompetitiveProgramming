/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dp on trees, rerooting, combinatorics
 * @idea
 *    - rerooting approach to combinatoric problem.
 *
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
const int maxn = 2e5 + 10;
vi g[maxn];
int dp[maxn];
int f[maxn], rf[maxn];
int r[maxn];
int sz[maxn];

int add(int a, int b) {
    return a + b < mod ? a + b : a + b - mod;
}

int mul(ll a, ll b) {
    return a * b % mod;
}

int comb(int n, int m) {
    if (m > n) return 0;
    return mul(f[n], mul(rf[m], rf[n - m]));
}

void dfs(int x, int p) {
    dp[x] = sz[x] = 1;
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
        sz[x] += sz[v];
    }
    int m = sz[x] - 1;
    for (int v : g[x]) {
        if (v == p) continue;
        dp[x] = mul(dp[x], mul(dp[v], comb(m, sz[v])));
        m -= sz[v];
    }
}

int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

void dfs_reroot(int x, int p) {
    if (p != 0) {
        int temp = mul(dp[p], ex(mul(comb(sz[p] - 1, sz[x]), dp[x]), mod - 2));
        dp[x] = mul(dp[x], mul(temp, comb(sz[p] - 1, sz[p] - sz[x])));
        sz[x] = sz[p];
    }
    for (int v : g[x]) {
        if (v == p) continue;
        dfs_reroot(v, x);
    }
}

class FDistributingIntegers {
public:

    void solveOne(istream& in, ostream& out) {
        f[0] = rf[0] = r[1] = 1;
        re(i, 1, maxn) {
            if (i > 1) {
                r[i] = mul(mod / i, mod - r[mod % i]);
            }
            f[i] = mul(i, f[i-1]);
            rf[i] = mul(r[i], rf[i-1]);
        }
        int n;
        in >> n;
        re(i, 1, n+1) {
            g[i].clear();
        }
        re(i, 1, n) {
            int a, b;
            in >> a >> b;
            g[a].eb(b);
            g[b].eb(a);
        }
        dfs(1, 0);
        dfs_reroot(1, 0);
        int ans = 0;
        re(i, 1, n+1) {
            out << dp[i] << endl;
        }
    }

    void solve(istream& in, ostream& out) {
        int testNumber = 1;
        //in >> testNumber;
        re(tc, 1, testNumber+1) {
            //out << "Case #" << tc << ": ";
            solveOne(in, out);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	FDistributingIntegers solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
