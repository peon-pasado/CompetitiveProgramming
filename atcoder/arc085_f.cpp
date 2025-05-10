/**
 * @author Miguel Mini
 * @tag dp, sweep_line, segment_tree
 * @idea
 *      - we can update with sweepline
 *      and normal order.
 * 
 *      - we can update dp[l][r]: best
 *      answer up to r taking the range
 *      (l, r).
 *  
 *      - we can update with dp[ll][rr]
 *      in two cases:
 *      
 *          1. rr < l
 * 
 *              in this case dp[l][r] = dp[ll][rr] + ones(rr+1, n) - ones(r+1, n) + zeros(l, r).
 * 
 *          2. ll <= l <= rr <= r
 * 
 *              in this case dp[l][r] = dp[ll][rr] + zeros(rr+1, n) - zeros(r+1, n)
 * 
 *      where:
 *  
 *          - ones(l, r): number of ones in b between l and r.
 *          - zeros(l, r): number of zeros in b between l and r.
 * 
 * 
 *      - as we use sweep line can avoid first argument. dp[l][r] -> dp[r].
 * 
 *      - we can save dp[r] + ones(r+1, n) and dp[r] + zeros(r+1, n)
 *      in a segment tree and query in ranges [0, l) and [l, r].
 *      
 * @complexity O(n\log n)
 */ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int inf = 1e9;
int b[maxn];
int n;

int get1(int l, int r) {
    if (r < l) return 0;
    return b[r] - b[l-1];
}

int get0(int l, int r) {
    if (r < l) return 0;
    return (r-l+1) - get1(l, r);
}

struct Node {
    int l, r;
} t[2 * maxn];
const Node nil = {inf, inf};

Node merge(Node p, Node q) {
    return {min(p.l, q.l), min(p.r, q.r)};
}

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = merge(t[i<<1], t[i<<1|1]);
}

void modify(int p, Node value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = merge(t[p], t[p^1]);
}

Node query(int l, int r) {  // sum on interval [l, r)
  Node res = nil;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = merge(res, t[l++]);
    if (r&1) res = merge(res, t[--r]);
  }
  return res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        b[i] += b[i-1];
    }
    n++;
    for (int i = 0; i < n; ++i) {
        t[n+i] = nil;
    }
    build();
    int q;
    cin >> q;
    vector<pair<int, int>> qu;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        qu.push_back({l, r});
    }
    sort(qu.begin(), qu.end());
    modify(0, {get0(1, n-1), get1(1, n-1)});
    int ans = get1(1, n-1);
    for (auto e : qu) {
        int dp1 = query(0, e.first).r - get1(e.first, n-1) + get0(e.first, e.second);
        int dp2 = query(e.first, e.second + 1).l - get0(e.second+1, n-1);
        int dpi = min(dp1, dp2);
        Node pii = {dpi + get0(e.second+1, n-1), dpi + get1(e.second+1, n-1)};
        ans = min(ans, pii.r);
        modify(e.second, pii);
    }
    cout << ans << endl;
    return 0;
}
