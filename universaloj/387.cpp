#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int p[maxn];
int h[maxn];
int deg[maxn];

int main() {
    int n, m;
    cin>>n>>m;
    for (int i=2; i<=n; ++i) {
        cin>>p[i];
        deg[p[i]]++;
    }
    h[1] = 0;
    for (int i=2; i<=n; ++i) {
        h[i] = h[p[i]] + 1;
    }
    priority_queue<pair<int, int>> pq;
    for (int i=1; i<=n; ++i) {
        if (deg[i] == 0) pq.push({h[i], i});
    }
    vector<vector<int>> s;
    int found = 0;
    while (found != n) {
        s.push_back(vector<int>());
        vector<int> nxt;
        int cf = 0;
        while (!pq.empty() && cf < m) {
            auto [h, v] = pq.top(); pq.pop();
            s.back().push_back(v);
            if (v != 1) {
                deg[p[v]]--;
                if (deg[p[v]] == 0) nxt.push_back(p[v]);
            }
            ++cf;
        }
        found += cf;
        for (auto u : nxt) {
            pq.push({h[u], u});
        }
    }
    reverse(s.begin(), s.end());
    cout << s.size() << '\n';
    for (auto vec : s) {
        cout << vec.size() << ' ';
        for (auto u : vec) {
            cout << u << ' ';
        }
        cout << '\n';
    }
    return 0;
}