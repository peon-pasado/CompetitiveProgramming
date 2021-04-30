/**
 * @author Miguel Mini
 * @tag dp
 * @idea
 *      - we can formulate
 *      dp(pos): len of the answer 
 *      to problem to suffix s[pos:].
 *  
 *      - dp[pos] = min(dp[pos], dp[nxt[pos][c]] + 1)
 * 
 *      - we can build the answer in 
 *      usual dp-build technique.
 * 
 * @complexity O(n sigma)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int nxt[maxn][30];
int dp[maxn];

int main() {
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < 26; ++i) nxt[n][i] = n;
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            nxt[i][j] = nxt[i+1][j];
        }
        nxt[i][s[i]-'a'] = i;
    }
    dp[n] = 1;
    for (int i = n-1; i >= 0; --i) {
        dp[i] = n+1;
        for (int j = 0; j < 26; ++j) {
            dp[i] = min(dp[i], dp[nxt[i+1][j]] + 1);
        }
    }
    int j = 0;
    for (int i = 0; i < 26; ++i) {
        if (dp[nxt[0][j]] > dp[nxt[0][i]]) {
            j = i;
        }
    }
    int len = dp[nxt[0][j]];
    int pos = 0;
    string ans;
    for (int i = 0; i < len; ++i) {
        int h = 0;
        for (int j = 0; j < 26; ++j) {
            if (dp[nxt[pos][j]] == len-i) {
                h = j;
                break;
            }
        }
        ans += 'a' + h;
        pos = nxt[pos][h] + 1;
    } 
    cout << ans << '\n';
    return 0;
}