/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag segment_tree, greedy, brute_force
 * @idea:
 *      - if we fix the number of swaps in n and n+1,
 *      the answer is the difference of inversions between 
 *      first half and second half.
 *
 *      - note that for a fixed number of swaps in n and n+1,
 *      this swaps need to be all 0-1 swaps or 1-0 swaps.
 *
 *      - if are 0-1 swaps, we need to shift the zeroes further 
 *      to the right and the ones further to the left and put 
 *      them at the ends, then we need i * i swaps to exchange 
 *      them, where i is the number of swaps in the middle 
 *      that were fixed. (symmetrically to 1-0 swaps).
 *
 *      note: This can be implemented in O(n), but with a segment 
 *      tree it makes implementation much easier in O(n \log n).
 *
 */

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <complex>
#include <climits>
#include <iomanip>
#include <numeric>
#include <functional>
#include <fstream>
#include <cassert>
#include <chrono>
#include <random>
#include <bitset>
#include <stack>
#define sz(x) (int)x.size()
#define trav(v, x) for (auto v : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define rep(x, y) for (int x=0; x<y; ++x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define set_to(x, v) fill(all(x), v)
#define eb emplace_back
#define lso(x) ((x)&-(x))
#define mset(m ,v) memset(m, v, sizeof(m))
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
using si = set<int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

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

const int inf = 1.2e9;
const int maxn = 2e5 + 10;

struct Node {
    ll inv;
    int zero, one;
} st[maxn<<2];
bitset<maxn> a;

Node merge(Node p, Node q) {
  return {
          p.inv + q.inv + p.one*1ll*q.zero,
          p.zero + q.zero,
          p.one + q.one
  };
}

int n;
void build(int nx=1, int l=0, int r=n-1) {
  if (l == r) {
    st[nx] = {0, !a[r], a[r]};
    return;
  }
  int mid = (l + r) / 2;
  build(nx<<1, l, mid);
  build(nx<<1|1, mid+1, r);
  st[nx] = merge(st[nx<<1], st[nx<<1|1]);
}

Node query(int ll, int rr, int nx=1, int l=0, int r=n-1) {
  if (rr < l || r < ll) return {0ll, 0, 0};
  if (ll <= l && r <= rr) return st[nx];
  int mid = (l + r) / 2;
  return merge(
          query(ll, rr, nx << 1, l, mid),
          query(ll, rr, nx << 1 | 1, mid + 1, r));
}

void update(int pos, int v, int nx=1, int l=0, int r=n-1) {
  if (pos < l || r < pos) return;
  if (l == r) {
    st[nx] = {0, !v, v};
    return;
  }
  int mid = (l + r) / 2;
  update(pos, v, nx<<1, l, mid);
  update(pos, v, nx<<1|1, mid+1, r);
  st[nx] = merge(st[nx<<1], st[nx<<1|1]);
}

class Gold_19mar_Balancing {
public:
    void solveOne(istream& in, ostream& out) {
      in >> n;
      n <<= 1;
      rep(i, n) {
        int x;
        in >> x;
        a[i] = x;
      }
      build();
      auto sol = []()->ll {
          return abs(query(0, n/2-1).inv - query(n/2, n-1).inv);
      };
      ll ans = sol();
      int l = n/2-1;
      int r = n/2;
      ll acc = 0;
      for (int i = 1; ; ++i) {
        while (l >= 0 && a[l] == 0) l -= 1;
        if (l < 0 || a[l] == 0) break;
        while (r < n && a[r] == 1) r += 1;
        if (r >= n || a[r] == 1) break;
        acc += ((n/2-i)-l) + (r-(n/2+i-1));
        update(l, 0);
        update(r, 1);
        ans = min(ans, acc + i *1ll* i + sol());
        l -= 1;
        r += 1;
      }
      build();
      l = n/2-1;
      r = n/2;
      acc = 0;
      for (int i = 1; ; ++i) {
        while (l >= 0 && a[l] == 1) l -= 1;
        if (l < 0 || a[l] == 1) break;
        while (r < n && a[r] == 0) r += 1;
        if (r >= n || a[r] == 0) break;
        acc += ((n / 2 - i) - l) + (r - (n / 2 + i - 1));
        update(l, 1);
        update(r, 0);
        ans = min(ans, acc + i *1ll* i + abs(sol()));
        l -= 1;
        r += 1;
      }
      out << ans << endl;
    }

    void solve(istream& in, ostream& out) {
      out.precision(10);
      out << fixed;
      int testNumber = 1;
      //in >> testNumber;
      re(tc, 1, testNumber+1) {
        //out << "Case #" << tc << ": ";
        solveOne(in, out);
      }
    }
};

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Gold_19mar_Balancing solver;
    std::istream& in(std::cin);
    std::ostream& out(std::cout);
    solver.solve(in, out);
    return 0;
}
