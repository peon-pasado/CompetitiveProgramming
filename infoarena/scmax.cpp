/**
 * @author Miguel Mini
 * @tag lis
 * @idea
 *      - lis algorithm.
 */ 

#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("scmax.in", "r", stdin);
    freopen("scmax.out", "w", stdout);
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    vector<int> lis = {0};
    vector<int> last(n, -1);
    for (int i = 1; i < n; ++i) {
        int lo = 0, hi = lis.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi-lo) / 2;
            if (a[lis[mid]] < a[i]) lo = mid+1;
            else hi = mid;
        }
        if (a[lis[lo]] < a[i]) {
            lis.push_back(i);
            last[i] = lis[lo];
        } else if (lo > 0) {
            lis[lo] = i;
            last[i] = lis[lo - 1];
        } else {
            lis[lo] = i;
        }
    }
    int cur = lis.back();
    vector<int> res;
    while (~cur) {
        res.push_back(a[cur]);
        cur = last[cur];
    }
    reverse(res.begin(), res.end());
    printf("%d\n", (int)res.size());
    for (auto e : res) printf("%d ", e);
    puts("");
    return 0;
}