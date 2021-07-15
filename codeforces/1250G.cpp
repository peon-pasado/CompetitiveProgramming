/**
 * @author Miguel Mini
 * @tag two_pointers, greedy
 * @idea
 *      - we can find the minimum
 *      prefix to win.
 * 
 *      - note that if we choose
 *      a prefix bigger answer
 *      cant be better.
 * 
 *      - we can wait for a reset
 *      until reach sum_a >= k, in
 *      this case we can erase all
 *      element before.
 * 
 * @complexity O(n)
 */ 
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        int l = 0, r = 0;
        long long sa = 0, sb = 0;
        long long pa = 0, pb = 0;
        while (r < n) {
            sa += a[r];
            sb += b[r];
            while (l < r && sa - min(pa, pb) >= k) {
                pa += a[l];
                pb += b[l];
                l++;
            }
            if (max(sa, sb) - min(pa, pb) >= k) break;
            r++;
        }
        if (sb - min(pa, pb) < k || sa - min(pa, pb) >= k) cout << -1 << '\n';
        else {
            int ans = 0;
            long long sa = 0, sb = 0;
            vector<int> res;
            for (int i = 0; i < l; ++i) {
                if (sa + a[i] >= k) {
                    res.push_back(i);
                    ans += 1;
                    if (sa > sb) {
                        sa -= sb;
                        sb = 0;
                    } else {
                        sb -= sa;
                        sa = 0;
                    }
                }
                sa += a[i];
                sb += b[i];
            }
            if (l > 0) {
                res.push_back(l);
                ans += 1;
            }
            cout << ans << '\n';
            for (auto r : res) cout << r << ' ';
            cout << '\n';
        }
    }
    return 0;
}