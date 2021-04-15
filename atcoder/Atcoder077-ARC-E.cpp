/**
 * @author Miguel Mini
 * @tag sweep_prefix
 * @idea
 *      - we can maintain answer
 *      for every initial position.
 * 
 *      - we can see that in each
 *      move ans is +distance(a_i, a_{i+1})
 *      and reduce by -j in path from
 *      a_i to a_{i+1}, this is a 
 *      quadratic equation from that path
 *      and we can solve with sweep prefix
 *      idea.
 * 
 * @complexity O(n+m)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn];
long long ans[maxn];

//update from l to r (-v + i - l)
void update(int l, int r, int v) {
    if (r < l) return;
    ans[l] -= v;
    ans[l+1] += v - 1;
    ans[r+1] += v + r - l + 1;
    ans[r+2] -= v + r - l;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long base = 0;
    for (int i = 0; i + 1 < n; ++i) {
        base += a[i+1] - a[i];
        if (a[i+1] < a[i]) {
            base += m;  
            update(a[i]+1, m, 0);
            update(1, a[i+1], m-a[i]);
        } else {
            update(a[i]+1, a[i+1], 0);
        }
    }
    for (int i = 1; i <= m; ++i) ans[i] += ans[i-1];
    for (int i = 1; i <= m; ++i) ans[i] += ans[i-1];
    cout << base + (*min_element(ans, ans+m+1)) << '\n';
    return 0;
}