/**
 * @author Miguel Mini
 * @tag greedy, binary_search, dp
 * @idea
 *      - A = (# odd degree nodes) / 2
 *      - we can fix B with a binary search
 *      and check with a dp.
 *      - to solve dp, we need open/close
 *      paths in odd-degree nodes.
 *      - dp(x): minimum path start on
 *      a subtree node of x and traverse
 *      this.
 *      - to merge subtrees of node x, we
 *      can sort lengths and match biggers
 *      with more fitting lengths.
 * @complexity O(n\log^2 n)       
 */ 
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <functional>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
    int r;
    for (r=1; b>0; b/=2) {
        if (b&1) r = mul(r, a, m);
        a = mul(a, a, m);
    }
    return r;
}

const int inf = 1.2e9;
const int max_n = 1e5 + 10;

struct Solver {
    int n;
    vector<int> g[max_n];
    void solve_one(istream &in, ostream &out) {
        in >> n;
        forn(i, n-1) {
            int a, b;
            in >> a >> b;
            g[a].emb(b);
            g[b].emb(a);
        }
        int A = 0;
        rep(i, 1, n+1) A += sz(g[i]) & 1;
        A /= 2;
        function<ii(int, int, int)> dfs = [&](int u, int p, int k)->ii {
            multiset<int> dps;
            ii ans{1, 0};
            trav(v, g[u]) {
                if (v == p) continue;
                auto son_res = dfs(v, u, k);
                ans.first &= son_res.first;
                dps.insert(son_res.second);
            }
            vi temp;
            while (sz(dps) > 1) {
                int gr = *dps.rbegin();
                dps.erase(dps.find(gr));
                if (*dps.begin() + gr > k) {
                    temp.psb(gr);
                } else {
                    auto ls = dps.upper_bound(k - gr);
                    --ls;
                    dps.erase(ls);
                }
            }
            if (sz(dps) == 1) temp.psb(*dps.begin());
            if (sz(temp) > 2) return {0, 0};
            if (sz(temp) > 0) ans.second = temp[sz(temp)-1] + (p!=0);
            else ans.second = (p != 0);
            if (ans.second > k) ans.first = 0;
            return ans;
        };
        auto predicate = [&](int x)->bool {
            rep(i, 1, n+1)
                if (sz(g[i]) == 1)
                    return dfs(i, 0, x).first;
            return false;
        };
        auto B = [&]()->int {
            int lo = 1, hi = n;
            while (lo < hi) {
                int mid = (lo+hi)/2;
                if (!predicate(mid)) lo = mid+1;
                else hi = mid;
            }
            return lo;
        };
        cout << A << ' ' << B() << '\n';  
    }
    void solve(istream &in, ostream &out) {
        out.precision(10);
        out << fixed;
        int test_number = 1;
        //in >> testNumber;
        forn(tc, test_number) {
            //out << "Case #" << tc+1 << ": ";
            solve_one(in, out);
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
        cin.exceptions(cin.failbit);
        solver.solve(cin, cout);
    }
    return 0;
}