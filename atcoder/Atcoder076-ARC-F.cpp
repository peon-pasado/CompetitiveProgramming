/**
 * @author Miguel Mini
 * @tag hall's_theorem, lazy_propagation
 * @idea
 *      - according to hall's theorem
 *      the answer is:
 * 
 *          max_{x < S} |x| - |R(x)|
 *           
 *      where R(x) is the imagen of x.
 * 
 *      -  we can force that R(x) is
 *      entire set or [1..l] \cup [r..m].
 * 
 * 
 *      - if is entire set, we 
 *      can assume that answer is n-m.     
 * 
 *      - in other case we can count this
 *      with a sweep line and segment_tree
 *      (update in range, query for maximum)     
 * 
 * @complexity O(n (\log n + \log m) + m)
**/ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>
#include <fstream>
#include <stack>
#include <queue>
#include <math.h>
#include <tuple>
#include <climits>
#define sz(x) ((int)x.size())
#define trav(v, x) for (auto v : x)
#define reu(x, y, z) for (int x=y; x<z; ++x)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;

int add(int a, int b, int m=mod) {
    return a+b < m? a+b : a+b-m;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%m;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;
const int maxn = 2e5 + 10;
int st[maxn << 2];
int lazy[maxn << 2];
int m;

void build(int nx=1, int l=0, int r=m+1) {
    if (l == r) {
        st[nx] = -(m+1-r);
        return;
    }
    int mid = (l+r)/2;
    build(nx<<1, l, mid);
    build(nx<<1|1, mid+1, r);
    st[nx] = max(st[nx<<1], st[nx<<1|1]);
}

void update(int L, int R, int nx=1, int l=0, int r=m+1) {
    if (R < l || r < L) return;
    if (L <= l && r <= R) {
        st[nx] += 1;
        lazy[nx] += 1;
        return;
    }
    int mid = (l + r) / 2;
    update(L, R, nx<<1, l, mid);
    update(L, R, nx<<1|1, mid+1, r);
    st[nx] = max(st[nx<<1], st[nx<<1|1]) + lazy[nx];
}

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
        int n;
        in >> n >> m;
        vii p(n);
        rep(i, n) {
            in >> p[i].first >> p[i].second;
        }
        build();
        int ans = n - m;
        sort(all(p));
        for (int i = 0; i < n; ++i) {
            update(p[i].first + 1, p[i].second);
            ans = max(ans, st[1] - p[i].first);
        }
        ans = max(ans, 0);
        out << ans << '\n';
    }
    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        //in >> testNumber;
        rep(tc, testNumber) {
            //out << "Case #" << tc+1 << ": ";
            solveOne(in, out);
        }
    }
};

int main() {
    Solver solver;
    string file = "";
    if (!file.empty()) {
      ifstream in(file + ".in");
      ofstream out(file + ".out");
      in.tie(nullptr);
      in.exceptions(in.failbit);
      solver.solve(in, out);
    } else {
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      solver.solve(cin, cout);
    }
    return 0;
}