/**
 * @author Miguel Mini
 * @tag string, greedy, dp, list
 * @idea
 *      - if p == 1
 *         
 *          - we can use a dp with two
 *          states, if if up to the 
 *          position and it ends in an 
 *          increasing or decreasing 
 *          sequence.
 * 
 *      - if p == 2
 * 
 *          - we can notice that answer
 *          is unique, we need to erase
 *          every element in any order.
 *      
 *          - we can erase from character
 *          with lowest value to highest
 *          ('a', ..., 'z').
 * 
 *          - we can maintain a list
 *          of current characters and 
 *          update in O(1).
 * 
 * @complexity O(n)
 */ 

#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("charlie.in", "r", stdin);
  freopen("charlie.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int p;
  string s;
  cin >> p >> s;
  int n = s.size();
  if (p == 1) {
    vector<vector<int>> dp(2, vector<int>(n));
    dp[0][0] = dp[1][0] = 1;
    for (int i = 1; i < n; ++i) {
      if (s[i] > s[i-1]) {
        dp[0][i] = 1;
        dp[1][i] = dp[0][i-1] + 1;
      } else if (s[i] < s[i-1]) {
        dp[0][i] = dp[1][i-1] + 1;
        dp[1][i] = 1;
      } else {
        dp[0][i] = dp[1][i] = 1;
      }
    }
    int ans = 1;
    for (int i = 0; i < 2; ++i) {
      for (int j = 1; j < n; ++j) {
        if (s[j-1] < s[j]) {
          ans = max(ans, dp[i][j] - (dp[i][j] % 2 == 0));  
        }
      }
    }
    cout << ans << '\n';
  } else {
    vector<int> adj[30];
    for (int i = 0; i < n; ++i) {
      adj[s[i] - 'a'].push_back(i);
    }
    int ans = 0;
    vector<int> nxt(n, -1), bck(n, -1);
    for (int i = 0; i + 1 < n; ++i) {
      nxt[i] = i+1;
    }
    for (int i = 1; i < n; ++i) {
      bck[i] = i-1;
    }
    for (int i = 0; i < 26; ++i) {
      for (int j : adj[i]) {
        if (j == 0 || j == n-1) continue;
        if (s[bck[j]] > s[j] && s[j] < s[nxt[j]]) {
          ans += max(s[bck[j]] - 'a', s[nxt[j]] - 'a') + 1;
          nxt[bck[j]] = nxt[j];
          bck[nxt[j]] = bck[j];
        }
      }
    }
    string res = "";
    for (int i = 0; ~i; i = nxt[i]) {
      res += s[i];
    }
    cout << res << '\n';
    cout << ans << '\n';
  }
  return 0;
}