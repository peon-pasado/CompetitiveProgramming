/**
 * @author Miguel Mini
 * @tag dsu, list
 * @idea
 *      - we can build edges
 *      from i from 1 to n 
 *      to colors and print
 *      numbers in the same
 *      component.
 * 
 *      - notice that time 
 *      limit is very strict. 
 * 
 * @complexity O(nk \alpha(n + 1001))
 */ 
#include <bits/stdc++.h>
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
    return a+b < mod? a+b : a+b-mod;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%mod;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;
const int maxn = 2010;
int head[maxn], nxt[1010];
int rnk[maxn], lnk[maxn];

void init(int i) {
  rnk[i] = 0;
  lnk[i] = i;
}

int get(int x) {
  return x == lnk[x] ? x : lnk[x] = get(lnk[x]);
}

void merge(int x, int y) {
  x = get(x); y = get(y);
  if (x == y) return;
  if (rnk[x] < rnk[y]) swap(x, y);
  rnk[x] += rnk[x] == rnk[y];
  lnk[y] = x;
}

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
      memset(head, -1, sizeof head);
      int n, k;
      in >> n >> k;
      for (int i = 0; i <= 1000 + n; ++i) {
        init(i);
      }
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
          int x;
          in >> x;
          merge(i, n + x);
        }
      }
      for (int i = n-1; i >= 0; --i) {
        nxt[i + 1] = head[get(i)];
        head[get(i)] = i + 1;
      }
      for (int i = 0; i <= 1000 + n; ++i) {
        if (head[i] == -1) continue;
        for (int v = head[i]; ~v; v = nxt[v]) {
          out << v << ' ';
        }
        out << '\n';
      }
    }
    void solve(istream& in, ostream& out) {
        //out.precision(10);
        //out << fixed;
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
    string file = "flori";
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