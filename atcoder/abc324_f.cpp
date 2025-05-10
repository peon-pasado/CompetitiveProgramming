#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
pair<int, int> edge[maxn];
vector<pair<int, int>> g[maxn];
double cst[maxn];
double bst[maxn];
int n, m;

bool p(double x) {
    for (int i=0; i<m; ++i) {
        cst[i] = edge[i].first - edge[i].second * x; 
    }   
    for (int i=1; i<=n; ++i) {
        bst[i] = -1e18;
    }
    bst[1] = 0;
    for (int i=2; i<=n; ++i) {
        for (auto [u, id] : g[i])
            bst[i] = max(bst[i], bst[u] + cst[id]);
    }
    return bst[n] >= 0;
}

int main() {
    cout << setprecision(10) << fixed;
    cin>>n>>m;
    for (int i=0; i<m; ++i) {
        int u, v, c, b;
        cin>>u>>v>>b>>c;
        edge[i] = {b, c};
        g[v].push_back({u, i});    
    }
    double lo = 0, hi = 2e9 + 10;
    for (int i=0; i<200; ++i) {
        double mi = (lo + hi) / 2;
        if (p(mi)) lo = mi;
        else hi = mi;
    }
    cout << lo << '\n';
    return 0;
}