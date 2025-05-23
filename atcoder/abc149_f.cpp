/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dp on trees, rerooting, combinatorics
 * @idea
 *      - rerooting and subset combinatorics problem
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

int add(int a, int b) {
    return a + b < mod ? a + b : a + b - mod;
}

int mul(ll a, ll b) {
    return a * b % mod;
}

int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b & 1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

int sz[maxn];
int inv2 = (mod + 1) / 2;
int dp[maxn];
void dfs(int x, int p) {
    sz[x] = 1;
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
        sz[x] += sz[v];
    }
    dp[x] = ex(inv2, sz[x]);
    for (int v : g[x]) {
        if (v == p) continue;
        dp[x] = add(dp[x], mul(ex(inv2, sz[x] - sz[v]), add(1, mod - ex(inv2, sz[v]))));
    }
}

void dfs_reroot(int x, int p) {
    if (p != 0) {
        dp[x] = mul(dp[x], ex(inv2, sz[p] - sz[x]));
        dp[x] = add(dp[x], mul(ex(inv2, sz[x]), add(1, mod - ex(inv2, sz[p] - sz[x]))));
        sz[x] = sz[p];
    }
    for (int v : g[x]) {
        if (v == p) continue;
        dfs_reroot(v, x);
    }
}

class FSurroundedNodes {
public:

    void solveOne(istream& in, ostream& out) {
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
        int res = 0;
        re(i, 1, n+1) {
            res = add(res, add(inv2, mod - dp[i]));
        }
        out << res << endl;
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
	FSurroundedNodes solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
