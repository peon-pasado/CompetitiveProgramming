/**
 * @author Miguel Mini
 * @tag dp, divide_and_conquer, sparse_table
 * @idea:
 *      - let be f(pos): best answer of ranges
 *      [i, pos] for all i in {1,..., pos}.
 *
 *      - let be g(pos) = maximum i that maximize
 *      f(pos).
 *
 *      - we can see that g(i) <= g(i+1).
 *
 *      - we can compute answer for range [i, j]
 *      in O(m).
 *
 *      - we can use divide and conquer, compute
 *      mid in range and maintain valid range for
 *      g(mid), we con note that sum of valid ranges
 *      for all i is O(n \log n).
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
const int maxm = 210;
using ll = long long;
ll a[maxn];
int b[maxn][maxm];
int st[maxn][14][maxm];
int n, m;

ll query(int l, int r) {
    int k = 31 - __builtin_clz(r-l+1);
    ll sum = 0;
    for (int i = 0; i < m; ++i) {
        sum += max(st[l][k][i], st[r-(1<<k)+1][k][i]);
    }
    return sum;
}

ll go(int _l, int _r, int l, int r) {
    if (r < l) return -1e18;
    int mid = (l + r) / 2;
    ll ans = -1e18;
    int pos = -1;
    for (int i = min(_r, mid); i >= _l; --i) {
        ll temp = query(i, mid) - (a[mid] - a[i]);
        if (ans < temp) {
            ans = temp;
            pos = i;
        }
    }
    ans = max(ans, go(_l, pos, l, mid-1));
    ans = max(ans, go(pos, _r, mid+1, r));
    return ans;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        cin >> a[i];
        a[i] += a[i-1];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> b[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            st[i][0][j] = b[i][j];
        }
    }
    for (int k = 1; k < 14; ++k) {
        for (int i = 0; i + (1<<k) <= n; ++i) {
            for (int j = 0; j < m; ++j) {
                st[i][k][j] = max(st[i][k-1][j], st[i+(1<<k-1)][k-1][j]);
            }
        }
    }
    cout << go(0, n-1, 0, n-1) << endl;
    return 0;
}