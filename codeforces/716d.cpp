#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 10;
const long long inf = 1e18;
using pii = pair<long long, int>;
vector<int> wedges;
vector<pair<int, int>> g[maxn];
long long d[maxn];
int p[maxn], pid[maxn];
int n, m;

void dijkstra(int s, int t, int x) {
    for (int i=0; i<n; ++i) d[i] = inf;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    d[s] = 0;
    p[s] = -1;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [w, q] = pq.top(); pq.pop();
        if (d[q] != w) continue;
        for (auto [r, id] : g[q]) {
            int we = wedges[id];
            if (we == 0) we += x;
            if (w + we < d[r]) {
                d[r] = w + we;
                p[r] = q;
                pid[r] = id;
                pq.emplace(d[r], r);
            }
        }
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int l, s, t;
    cin>>n>>m>>l>>s>>t;
    vector<pii> edges;
    vector<int> ze;
    for (int i=0; i<m; ++i) {
        int u, v, w;
        cin>>u>>v>>w;
        edges.emplace_back(u, v);
        wedges.emplace_back(w);
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    dijkstra(s, t, l+1);
    if (d[t] == inf || d[t] < l) {
        cout << "NO\n";
        return 0;
    }
    dijkstra(s, t, 1);
    if (d[t] > l) {
        cout << "NO\n";
        return 0;
    }
    int x = t;
    while (x != s) {
        if (wedges[pid[x]] == 0) {
            ze.emplace_back(pid[x]);
            wedges[pid[x]] = 1;
        }
        x = p[x];
    }
    for (int i=0; i<m; ++i) {
        if (wedges[i] == 0) {
            wedges[i] = l+1;
        }
    }
    if (d[t] == l) {
        cout << "YES\n";
        for (int i=0; i<m; ++i) {
            cout << edges[i].first << " " << edges[i].second << " " << wedges[i] << '\n';
        }
        return 0;
    }

    for (auto e : ze) {
        wedges[e] += l - d[t];
        dijkstra(s, t, 0);
        if (d[t] == l) {
            cout << "YES\n";
            for (int i=0; i<m; ++i) {
                cout << edges[i].first << " " << edges[i].second << " " << wedges[i] << '\n';
            }
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}