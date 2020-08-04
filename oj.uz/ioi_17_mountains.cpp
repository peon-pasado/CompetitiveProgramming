/**
 * @problem ioi 2017 Mountains
 * @tag dp, convex_hull
 * @idea
 *      - we can build a dp[l][r] which indicates
 *      the maximum number of elements that can be
 *      taken from the range [l, r]
 *
 *      - if we don't use "l", clearly the answer
 *      would be dp[l][r] = dp[l+1][r], otherwise, 
 *      I consider the furthest element "l" can see, 
 *      and I consider dp[l][r] = dp[l][last-1] + dp[last+1][r].     
 */

#include "mountains.h"
#include <bits/stdc++.h>

int maximum_deevs(std::vector<int> y) {
  int n = y.size();
  std::vector<int> last(n, -1);
  std::vector<std::vector<int>> memo(n+1, std::vector<int>(n+1, 0));
  for (int i = 0; i < n; ++i) {
    memo[i][i] = 1;
  }
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i < n; ++i) {
      int nxt = i + len - 1;
      if (nxt >= n) continue;
      memo[i][nxt] = memo[i+1][nxt];
      if (last[i] == -1 ||
          (last[i] - i) *1ll* (y[nxt] - y[i]) >= (nxt - i) *1ll* (y[last[i]] - y[i])) {
        last[i] = nxt;
      }
      memo[i][nxt] = std::max(memo[i][nxt], memo[i][last[i]-1] + memo[last[i]+1][nxt]);
    }
  }
  return memo[0][n-1];
}
