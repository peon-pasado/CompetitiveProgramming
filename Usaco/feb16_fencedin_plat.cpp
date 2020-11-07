/**
 *  @author Miguel Mini
 *  @tag mst, priority_queue
 *  @idea
 *      - use simple mst approach.
 *
 *      - this is a patron for every
 *      abcsissa, except for first element. 
 *
**/

#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    int a, b, n, m;
    cin >> a >> b >> n >> m;
    vector<int> u(n+2), v(m+2);
    for (int i = 0; i < n; ++i) cin >> u[i];
    for (int i = 0; i < m; ++i) cin >> v[i];
    u[n+1] = a;
    v[m+1] = b;
    sort(u.begin(), u.end());
    sort(v.begin(), v.end());
    u.resize(unique(u.begin(), u.end()) - u.begin());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    using ii = pair<int, int>;
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    for (int i = 1; i < u.size(); ++i) Q.push({u[i] - u[i-1], 0}); 
    for (int i = 1; i < v.size(); ++i) Q.push({v[i] - v[i-1], 1});
    long long ans = 0;
    int l = (int)u.size() - 2, r = (int)v.size() - 2;
    bool bl = 0, br = 0;
    while (!Q.empty()) {
        auto q = Q.top(); Q.pop();
        if (q.second) {
            if (br) {
                ans += q.first *1ll* l;
            } else {
                ans += q.first *1ll* ((int)u.size() - 2);
            }
            r -= br;
            br = 1;
        } else {
            if (bl) {
                ans += q.first *1ll* r;
            } else {
                ans += q.first *1ll* ((int)v.size() - 2);
            }
            l -= bl;
            bl = 1;
        }
    }
    cout << ans << endl;
    return 0;
}
