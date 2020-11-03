/**
 *  @author Miguel Mini
 *  @tag sorting, fenwick_tree
 *  @idea
 *      - use prefix accumulate version 
 *      of array a with n + 1 elements.
 *
 *      - we need count to i > j how many
 *      values are: (s[i] - s[j]) / (i - j) >= p
 *
 *      - we can sort the values and count
 *      number of inversions in result permutation.
**/

#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e6 + 10;
using ll = long long;
ll a[maxn];
int n, p;
int ft[maxn];
 
void upd(int pos, int v) {
    while (pos < maxn) {
        ft[pos] += v;
        pos += pos&-pos;
    }
}
 
int qry(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += ft[pos];
        pos -= pos&-pos;
    }
    return ans;
}
 
int main() {
    scanf("%d", &n);
    vector<int> id(n + 1);
    iota(id.begin(), id.end(), 0);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld\n", a+i);
        a[i] += a[i-1];
    }
    scanf("%d", &p);
    stable_sort(id.begin(), id.end(), [](int i, int j) {
        return a[i] - i *1ll* p < a[j] - j *1ll* p;
    });
    long long ans = 0;
    for (int i : id) {
        ans += qry(i);
        upd(i + 1, 1);
    }
    printf("%lld\n", ans);
    return 0;
}
