#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int p[maxn], rnk[maxn];
vector<int> r[maxn];

int get(int x) {
    return x == p[x] ? x : p[x] = get(p[x]);
}

void merge(int u, int v) {
    u = get(u); v = get(v);
    if (rnk[u] < rnk[v]) swap(u, v);
    rnk[u] += rnk[u] == rnk[v];
    p[v] = u;
    for (auto w : r[v]) r[u].push_back(w);
    sort(r[u].rbegin(), r[u].rend());
    if (r[u].size() > 10) r[u].resize(10); 
}

int main() {
    int n, q;
    cin>>n>>q;
    for (int i=1; i<=n; ++i) {
        p[i] = i;
        rnk[i] = 0;
        r[i].push_back(i);
    }
    for (int i=0; i<q; ++i) {
        int type;
        cin>>type;
        if (type == 1) {
            int u, v;
            cin>>u>>v;
            if (get(u) != get(v)) {
                merge(u, v);
            }
        } else {
            int v, k;
            cin>>v>>k;
            v = get(v);
            if (r[v].size() < k) cout << -1 << '\n';
            else cout << r[v][k-1] << '\n';
        }
    }
    return 0;
}