/**
 *  @author Miguel Mini
 *  @tag coordinate_compression, segment_tree, sweep_line, binary_search, math
 *  @idea 
 *
 *      - use sweep_line over coordinates.
 *
 *      - maintain hyperplanes with two segment trees.
 *
 *      - note that max_right - max_left is monotone,
 *      use lower and upper bound over 0 to obtain minimum.
 *
 *  @complexity: O(n (\log n + \log^2 1e5) + 1e5)
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int st[2][4 * maxn];
int cnt[maxn];
int n, m;

void build(int nx=1, int l=0, int r=maxn-1) {
  if (l == r) {
    st[0][nx] = cnt[r];
    return;
  }
  int mid = (l+r)/2;
  build(nx<<1, l, mid);
  build(nx<<1|1, mid+1, r);
  st[0][nx] = st[0][nx<<1] + st[0][nx<<1|1];
}

void update(int pos, int nx=1, int l=0, int r=maxn-1) {
  if (pos < l || pos > r) return;
  if (l == r) {
    st[0][nx] -= 1;
    st[1][nx] += 1;
    return;
  }
  int mid = (l + r) / 2;
  update(pos, nx<<1, l, mid);
  update(pos, nx<<1|1, mid+1, r);
  st[0][nx] = st[0][nx<<1] + st[0][nx<<1|1];
  st[1][nx] = st[1][nx<<1] + st[1][nx<<1|1];
}

const int inf = 1e9;
pair<int, int> query(int ll, int rr, int nx=1, int l=0, int r=maxn-1) {
  if (rr < l || r < ll) return {0, 0};
  if (ll <= l && r <= rr) return {st[0][nx], st[1][nx]};
  int mid = (l+r)/2;
  auto L = query(ll, rr, nx<<1, l, mid);
  auto R = query(ll, rr, nx<<1|1, mid+1, r);
  return {L.first + R.first, L.second + R.second};
}

int solve() {
  auto get = [&](int x)->pair<int, int> {
      auto q = query(0, x);
      int t1 = max(q.first, q.second);
      int t2 = max(st[0][1] - q.first, st[1][1] - q.second);
      return {t1, t2};
  };
  int lo = 0, hi = maxn-1;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    auto q = get(mid);
    if (q.second - q.first >= 0) lo = mid;
    else hi = mid-1;
  }
  auto q = get(lo);
  int ans1 = max(q.first, q.second);
  lo = 0; hi = maxn-1;
  while (lo < hi) {
    int mid = (lo + hi) / 2;
    auto q = get(mid);
    if (q.second - q.first > 0) lo = mid+1;
    else hi = mid;
  }
  q = get(lo);
  int ans2 = max(q.first, q.second);
  return min(ans1, ans2);
}

using pii = pair<int, int>;
int main() {
  freopen("balancing.in", "r", stdin);
  freopen("balancing.out", "w", stdout);
  cin >> n;
  map<int, int> X, Y;
  vector<pii> p(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    X[x]; Y[y];
    p[i] = {x, y};
  }
  int tx = 0, ty = 0;
  for (auto& e : X) e.second = tx++;
  for (auto& e : Y) e.second = ty++;
  for (auto& e : p) e = {X[e.first], Y[e.second]};
  sort(p.begin(), p.end(), [&](pii p, pii q) {
      return p.second < q.second;
  });
  for (auto e : p) cnt[e.first] += 1;
  build();
  int ans = solve();
  for (int i = 0; i < p.size();) {
    int j = i;
    while (j < p.size() && p[j].second == p[i].second) {
      update(p[j].first);
      j += 1;
    }
    ans = min(ans, solve());
    i = j;
  }
  cout << ans << endl;
  return 0;
}
