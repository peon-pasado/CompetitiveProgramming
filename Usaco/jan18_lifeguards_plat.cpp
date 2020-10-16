/**
 *  @author Miguel Mini
 *  @tag dp, fenwick tree
 *  @idea
 *    - Suppose the segments ordered by r, we can find the 
 *    dp(x, k): maximum length using the first x elements in
 *    such a way that the element x is used and eliminating 
 *    k from them, infinite if not possible.
 *
 *    - We can separate the dp in two cases, 1. we do not use 
 *    elements that overlap with segment x or 2. use at least 
 *    one element that overlaps with segment x.
 *  
 *    - In the first case we eliminate all the elements that 
 *    overlap with segment x and find the best way to take elements 
 *    that do not overlap with segment x, we can do this with 
 *    another simple dp.  
 *
 *    - In the second case we greedily take the leftmost element 
 *    that overlaps with segment x and use all the leftover elements 
 *    as wildcards. We can use a binary search to find the first
 *    overlaping segment and a fenwick tree to get the leftmost.
 *
 *  @complexity O(nk)
**/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int ft[maxn];
int dp[maxn][110], rangeDp[maxn][110];
struct Point {
    int l, r;
} p[maxn];
int n, k;

void upd(int x) {
    int pos = x;
    x = n - x;
    while (x < maxn) {
        if (p[ft[x]].l > p[pos].l) {
            ft[x] = pos;
        }
        x += x&-x;
    }
}

int qry(int x) {
    int ans = n;
    x = n - x;
    while (x > 0) {
        if (p[ans].l > p[ft[x]].l) {
            ans = ft[x];
        }
        x -= x&-x;
    }
    return ans;
}

int main() {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].l >> p[i].r;
    }
    const int inf = 1.1e9;
    p[n].l = inf;
    for (int i = 1; i < maxn; ++i) ft[i] = n; 
    sort(p, p+n, [](Point p, Point q) {
        return p.r < q.r;        
    });
    for (int i = 0; i < n; ++i) {
        fill(dp[i], dp[i]+k+1, -inf);
        fill(rangeDp[i], rangeDp[i]+k+1, -inf);
    }
    dp[0][0] = rangeDp[0][0] = p[0].r - p[0].l;
    dp[0][1] = -inf;
    rangeDp[0][1] = 0;
    upd(0);
    for (int i = 1; i < n; ++i) {
        int lo = 0, hi = i-1;
        while (lo < hi) {
            int mid = lo+(hi-lo)/2;
            if (p[mid].r < p[i].l) lo=mid+1;
            else hi=mid;
        }
        if (p[lo].r > p[i].l) {
            int x = qry(lo);
            if (p[x].l > p[i].l) {
                int alpha = i - lo;
                int delta = p[i].r - p[i].l;
                for (int j = 0; j <= min(k, i); ++j) {
                    dp[i][j] = (!lo ? 0 : rangeDp[lo-1][max(0, j - alpha)]) + delta;
                }
            } else {
                int alpha1 = i-x-1;
                int delta1 = p[i].r - p[x].r;
                for (int j = 0; j <= min(i, k); ++j) {
                    dp[i][j] = dp[x][max(0, j - alpha1)] + delta1;
                }
                int alpha2 = i-lo;
                int delta2 = p[i].r - p[i].l;
                for (int j = alpha2; j <= min(i, k); ++j) {
                    dp[i][j] = max(dp[i][j], (!lo ? 0 : rangeDp[lo-1][j-alpha2]) + delta2);
                }
            }
        } else {
            int delta = p[i].r - p[i].l;
            for (int j = 0; j <= min(i, k); ++j) {
                dp[i][j] = rangeDp[i-1][j] + delta;
            }
        }
        rangeDp[i][0] = dp[i][0];
        for (int j = 1; j <= k; ++j) {
            rangeDp[i][j] = max(dp[i][j], rangeDp[i-1][j-1]);
        }
        upd(i);
    }
    cout << rangeDp[n-1][k] << endl;
    return 0;
}
