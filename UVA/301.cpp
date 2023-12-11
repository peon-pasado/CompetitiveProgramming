/**
 *  @idea backtracking, pruning 
 * 
 *  - we can simulate, and pruning 
 *  simulate travel in order of stations,
 *  we need to prune by passengers.
 * 
 *  - we can also prune adding a sum
 *  all picks in before parades.
 * 
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;
int n, m, q;
vector<pair<int, int>> edges[maxn];
int bt(int px, int py, int pa, int out[]) {
    if (px == m + 1) return 0;
    if (py == 0) pa -= out[px];
    if (py == (int)edges[px].size()) return bt(px+1, 0, pa, out);
    int ans = bt(px, py+1, pa, out);
    if (pa + edges[px][py].second <= n) {
        out[edges[px][py].first] += edges[px][py].second;
        ans = max(ans, bt(px, py+1, pa + edges[px][py].second, out) + edges[px][py].second * (edges[px][py].first - px));
        out[edges[px][py].first] -= edges[px][py].second;
    }
    return ans;
}


int main() {    
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin>>n>>m>>q, n+m+q) {
        for (int i=0; i<=m; ++i) {
            edges[i].clear();
        }
        for (int i=0; i<q; ++i) {
            int a, b, c;
            cin>>a>>b>>c;
            edges[a].push_back({b, c});
        }
        int out[10];
        for (int i=0; i<=m; ++i) out[i] = 0;
        cout << bt(0, 0, 0, out) << '\n';
    }
    return 0;
}