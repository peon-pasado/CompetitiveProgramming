/**
 * @author Miguel Mini
 * @tag dp, dfs, prefix, number_theory, periods
 * @idea
 *      - we can note that the answer
 *      is 1, 2 or n:
 *
 *          - if w is non-periodic the answer is 1
 *
 *          - if w = c^n the answer is n
 *
 *          - in other case w = t^m with |t| > 1
 *          and t is non-periodic then:
 *
 *              w = (t^{m-1} u, c)
 *
 *          with c a character and u such that t = u c
 *
 *      - to compute the number of ways of case "answer = 2"
 *      we can build borders(w) and borders(reverse(w))
 *
 *      - and build for each of these a prefix-tree:
 *
 *          - the directed edges are (b[i], i) for all i in [1..n]
 *
 *      - with these trees we need to answer if a prefix
 *      if non-periodic.
 *
 *      Lemma: A string s is non-periodic is |s| - b^k(|s|) just
 *      divide |s| if |b^k(s)| = 0.
 *
 *      - we can answer this with a dfs and check if an ancestor
 *      v of x meets x - divisor = v for all divisor of x.
 *
 * @complexity O(n \log n)
 */

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
vi prefix(string& s) {
    vi b(s.size() + 1);
    b[0] = -1;
    for (int i = 1; i <= s.size(); ++i) {
        int& j = b[i] = b[i-1];
        while (~j && s[i-1] != s[j]) j = b[j];
        ++j;
    }
    return b;
}

const int maxn = 5e5 + 10;
vector<int> gl[maxn], gr[maxn];
int cnt[maxn];
int dpl[maxn], dpr[maxn];
bool vis[maxn];
vector<int> di[maxn];


void dfs(int x, vi g[], int dp[]) {
    cnt[x] = 1;
    bool is1 = true;
    for (int d : di[x]) {
        if (cnt[x - d]) {
            is1 = false;
            break;
        }
    }
    dp[x] = is1;
    for (int v : g[x]) {
        dfs(v, g, dp);
    }
    cnt[x] = 0;
}


int main() {
    string w;
    cin >> w;
    auto bl = prefix(w);
    reverse(w.begin(), w.end());
    auto br = prefix(w);
    int n = w.size();
    if (bl[n] == n-1) {
        cout << n << '\n';
        cout << 1 << '\n';
        return 0;
    }
    int mb = n;
    while (~mb) {
        if (n % (n - bl[mb]) == 0) {
            mb = n - bl[mb];
            break;
        }
        mb = bl[mb];
    }
    if (mb == n) {
        cout << 1 << '\n';
        cout << 1 << '\n';
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        gl[bl[i]].push_back(i);
        gr[br[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 2*i; j <= n; j += i) {
            di[j].push_back(i);
        }
    }
    dfs(0, gl, dpl);
    dfs(0, gr, dpr);
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (dpl[i] && dpr[n-i]) {
            ans += 1;
        }
    }
    cout << 2 << '\n';
    cout << ans << '\n';
    return 0;
}