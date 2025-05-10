/**
 * @author Miguel Mini
 * @tag sorting, monotonic stack
 * @idea
 *      - we can note that positions
 *      in the lexicographic monotone
 *      increasing sequence starting in
 *      first position have positive
 *      contribution.
 *
 *      - answer for i-th valid position
 *      is the number of block above of
 *      height of (i-1)-th valid position.
 *
 *      - we can sort and count this in
 *      O(n \log n).
 *
 *  @complexity O(n \log n)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    using ll = long long;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<int> s;
    for (int i = n; i >= 0; --i) {
        while (!s.empty() && a[s.back()] <= a[i]) {
            s.pop_back();
        }
        s.push_back(i);
    }
    vector<pair<int, int>> b(n + 1);
    for (int i = 0; i <= n; ++i) {
        b[i] = {a[i], i};
    }
    sort(b.rbegin(), b.rend());
    ll sum = 0;
    vector<ll> ans(n + 1);
    for (int i = 0, j = 1; i < b.size(); ++i) {
        sum += b[i].first;
        if (b[i].second == s[j]) {
            ll temp = sum - (i + 1) *1ll* b[i].first;
            ans[s[j-1]] = temp;
            sum -= temp;
            j += 1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}