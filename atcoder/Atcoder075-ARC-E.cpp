/**
 * @author Miguel Mini
 * @tag sorting, BIT
 * @idea
 *      - we need number of
 *      pairs (l, r), 0 <= l <= r <= n
 *      such that:
 *  
 *          sum_{1 <= i <= r} a_r 
 *              - sum_{1 <= i <= r} a_l <= k * (r - l)
 * 
 *      - then we need number of inversions
 *      after of sorting pairs:
 * 
 *           (sum_{1 <= i <= j} a_j - k * j, j) 
 * 
 * @complexity O(n \log n)
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 2e5 + 10;
int ft[maxn];

void update(int x, int v) {
    while (x < maxn) {
        ft[x] += v;
        x |= (x+1);
    }
} 

int query(int x) {
    int ans = 0;
    while (x >= 0) {
        ans += ft[x];
        x = (x&(x+1)) - 1;
    }
    return ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<long long> acc(n + 1);
    for (int i = 0; i < n; ++i) {
        acc[i+1] = acc[i] + a[i];
    }
    vector<pair<long long, int>> b(n+1);
    for (int i = 0; i <= n; ++i) {
        b[i] = {acc[i] - k *1ll* i, i};
    }
    sort(b.begin(), b.end());
    long long ans = 0;
    for (auto e : b) {
        ans += query(e.second);
        update(e.second, 1);
    }
    cout << ans << endl;
    return 0;
}