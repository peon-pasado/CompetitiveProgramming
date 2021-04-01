/**
 * @author Miguel Mini
 * @tag prefix_sum, sets, sweep_line
 * @idea
 *      - first part:
 
 *          - sum 1 to ranges (l_i, r_i).
 *          k = max_sum. 
 * 
 *      - second part:
 * 
 *          - sort ranges by L, maintain
 *          ordered set of active ranges
 *          and multiply k - #active_ranges.
 * 
 * @complexity O(n \log n)
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e4 + 10;
struct Node {
    int l, r;
} p[maxn];
int cnt[maxn];

int main() {
    freopen("ben.in", "r", stdin);
    freopen("ben.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].l >> p[i].r;
    }
    for (int i = 0; i < n; ++i) {
        cnt[p[i].l]++;
        cnt[p[i].r+1]--;
    }
    for (int i = 1; i < maxn; ++i) cnt[i] += cnt[i-1];
    int k = *max_element(cnt, cnt+maxn);
    printf("%d ", k);
    sort(p, p+n, [](Node p, Node q) {
       return p.l < q.l; 
    });
    const int mod = 32173;
    int res = 1;
    multiset<int> s;
    int oc = 0;
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && *s.begin() < p[i].l) {
            s.erase(s.begin());
            oc--;
        }
        res = res * (k - oc) % mod;
        oc++;
        s.insert(p[i].r);
    }
    printf("%d\n", res);
    return 0;
}