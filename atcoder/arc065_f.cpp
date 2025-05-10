/**
 * @author Miguel Mini
 * @tag dp, amortized
 * @idea
 *      - we can make dp
 *
 *          dp(position, cnt_0, cnt_1, last_position)
 *
 *              - position: current_position in string
 *              - cnt_x: number of available x in position
 *              - last_position: maximum r of ranges with l <= position
 *
 *      - yes, this dp can be O(n^5). If we avoid operations
 *      with same l. we can see that update last position
 *      in a specific position is amortized (current complexity: O(n^4)).
 *
 *      - O(n^3): but... in this case last position is a function of position.
 *
 *      - O(n^2): we can note that cnt_x is a function of position and cnt_{1-x}.
 *
 * @complexity: O(n^2)
 */

#include <iostream>
using namespace std;

const int maxn = 3010;
const int mod = 1e9 + 7;
int r[maxn];
string s;
int n, m;

bool vis[maxn][maxn];
int memo[maxn][maxn];
int dp(int pos, int cnt0, int cnt1, int last) {
    if (pos == n) return 1;
    if (vis[pos][cnt0]) return memo[pos][cnt0];
    vis[pos][cnt0] = 1;
    int& ans = memo[pos][cnt0] = 0;
    for (int i = last+1; i <= r[pos]; ++i) {
        cnt0 += s[i] == '0';
        cnt1 += s[i] == '1';
    }
    last = max(last, r[pos]);
    if (cnt0 > 0) ans += dp(pos+1, cnt0-1, cnt1, last);
    if (cnt1 > 0) ans += dp(pos+1, cnt0, cnt1-1, last);
    if (ans >= mod) ans -= mod;
    return ans;
}

int main() {
    cin >> n >> m >> s;
    for (int i = 0; i < n; ++i) r[i] = i;
    while (m--) {
        int L, R;
        cin >> L >> R;
        L--; R--;
        r[L] = max(r[L], R);
    }
    cout << dp(0, 0, 0, -1) << '\n';
    return 0;
}