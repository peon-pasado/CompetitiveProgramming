/**
 * @author Miguel Mini
 * @tag sqrt_decomposition, binary_search
 * @idea
 *      - we can use classic array partition
 *      sqrt decomposition approach with
 *      B = sqrt(n log n)
 *
 *      - we can build the array in O(n)
 *
 *      - and solve with binary search to
 *      merge two blocks in: O(n / B * log B).
 *
 * @complexity O(n \sqrt(n / \log(n)))
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int x[maxn];
int n, q, l;
using ii = pair<int, int>;
ii bans[maxn];
int sn;

void build(int b) {
    int j = min(n, (b+1)*sn) - 1;
    int jend = j;
    for (int i = jend; i >= b * sn; --i) {
        while (x[j] - x[i] > l) j -= 1;
        if (jend == j) bans[i] = {0, l - (x[j] - x[i])};
        else {
            bans[i] = bans[j];
            bans[i].first += 1;
        }
    }
}

int query(int a, int b) {
    int sa = a / sn;
    int sb = b / sn;
    ii ans = {0, l};
    if (sa == sb) {
        for (int i = a + 1; i <= b; ++i) {
            if (x[i] - x[i-1] <= ans.second) {
                ans.second -= x[i] - x[i-1];
            } else {
                ans.first += 1;
                ans.second = l - (x[i] - x[i-1]);
            }
        }
    } else {
        for (int i = a + 1; i < (sa+1)*sn; ++i) {
            if (x[i] - x[i-1] <= ans.second) {
                ans.second -= x[i] - x[i-1];
            } else {
                ans.first += 1;
                ans.second = l - (x[i] - x[i-1]);
            }
        }
        for (int i = sa+1; i < sb; ++i) {
            if (x[i*sn] - x[i*sn-1] > ans.second) {
                ans.first += 1;
                ans.second = l;
            }
            int lo = i*sn, hi = (i+1)*sn-1;
            while (lo < hi) {
                int mid = (lo + hi + 1) / 2;
                if (x[mid] - x[i*sn-1] <= ans.second) lo = mid;
                else hi = mid-1;
            }
            if (lo < (i + 1)*sn - 1) {
                ans.first += 1;
                ans.first += bans[lo].first;
                ans.second = bans[lo].second;
            } else {
                ans.second -= x[lo] - x[i*sn-1];
            }
        }
        for (int i = sb*sn; i <= b; ++i) {
            if (x[i] - x[i-1] <= ans.second) {
                ans.second -= x[i] - x[i-1];
            } else {
                ans.first += 1;
                ans.second = l - (x[i] - x[i-1]);
            }
        }
    }
    ans.first += 1;
    return ans.first;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> x[i];
    cin >> l;
    sn = max(2, (int)sqrt(n * log(n)));
    for (int i = 0; i < n/sn; ++i) {
        build(i);
    }
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (a > b) swap(a, b);
        cout << query(a, b) << '\n';
    }
    return 0;
}