/**
 * @author Miguel Mini
 * @tag hashing, brute_force, dsu
 * @idea
 *      - if n < k, brute force solution is enough.
 *
 *      - in other case, erase two characters
 *      and verify for all string, obviusly with
 *      string hashing.
 *
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e4 + 10;
string s[maxn];
int t, n, k;
bool vis[maxn];
const int base = 257;
using ll=long long;
ll R[maxn], B[maxn];
int rnk[maxn], link[maxn];

int get(int x) {
    return link[x] != x ? link[x] = get(link[x]) : x;
}

void merge(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) {
        swap(x, y);
    }
    rnk[x] += rnk[x] == rnk[y];
    link[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    B[0] = 1;
    for (int i = 1; i < maxn; ++i) B[i] = B[i-1] * base;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i=0; i<n; ++i) {
            cin >> s[i];
        }
        if (k <= 2) {
            for (int i = 0; i < n; ++i) {
                vis[i] = 1;
            }
        } else if (n <= 2700) {
            for (int i = 0; i < n; ++i) {
                vis[i] = 0;
            }
            for (int i = 0; i < n; ++i) {
                for (int j = i+1; j < n; ++j) {
                    int m_match = 0;
                    for (int d = 0; d < k; ++d) {
                        m_match += s[i][d] != s[j][d];
                    }
                    if (m_match <= 2) {
                        vis[i] = vis[j] = 1;
                    }
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                link[i] = i;
                rnk[i] = 0;
            }
            unordered_map<ll, int> cnt[k][k];
            R[k] = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = k-1; j >= 0; --j) {
                    R[j] = R[j+1] * base + s[i][j]; 
                }
                ll h1=0;
                for (int j = 0; j < k; ++j) {
                    ll h2 = h1;
                    for (int d = j+1; d < k; ++d) {
                        ll cur = h2 + R[d+1] * B[d-1];
                        if (cnt[j][d].count(cur)) merge(i, cnt[j][d][cur]);
                        cnt[j][d][cur] = i;
                        h2 = h2 + s[i][d] * B[d-1];
                    }
                    h1 = h1 + s[i][j] * B[j];
                }
            }
            for (int i = 0; i < n; ++i) {
                vis[i] = rnk[get(i)] != 0; 
            }
        }
        string result;
        for (int i = 0; i < n; ++i) {
            result += "01"[vis[i]];
        }
        cout << result << endl;
    }
    return 0;
}
