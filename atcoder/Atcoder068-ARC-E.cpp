/**
 * @author Miguel Mini
 * @tag number_theory, fenwick_tree, sweep_line
 * @idea
 *      - number of train parades is O(n \log n)
 *      - if range r_i - l_i + 1 >= d then range
 *      i intercept train d.
 *      - if r_i - l_i + 1 < d thne range i
 *      intercept at most one train d parades.
 *      - we can sort ranges and add these
 *      if r_i - l_i + 1 < d, others range
 *      add 1 to answer.
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;
int l[maxn], r[maxn];
pair<int, int> p[maxn];
int ft[maxn];
int n, m;

void update(int pos, int x) {
    while (pos <= m) {
        ft[pos] += x;
        pos |= pos+1;
    }
}

int query(int pos) {
    int ans = 0;
    while (pos >= 0) {
        ans += ft[pos];
        pos = (pos&(pos+1)) - 1;
    }
    return ans;
}


int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    for (int i = 0; i < n; ++i) p[i] = {r[i]-l[i]+1, i};
    sort(p, p+n);
    int tans = n;
    for (int d = 1, j = 0; d <= m; ++d) {
        while (j < n && p[j].first < d) {
            tans -= 1;
            update(l[p[j].second], 1);
            update(r[p[j].second] + 1, -1);
            j += 1;
        }
        int ans = 0;
        for (int j = 0; j <= m; j += d) {
            ans += query(j);
        }
        printf("%d\n", tans + ans);
    }
    return 0;
}