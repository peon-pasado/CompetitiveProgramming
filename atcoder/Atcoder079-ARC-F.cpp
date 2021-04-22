/**
 * @author Miguel Mini
 * @tag grundy, brute_force, dfs
 * @idea
 *      - if the graph doesnt has cycles
 *      we can use grundy number to 
 *      obtain values.
 *  
 *      - in other case, nodes in a cycle
 *      can have two values: (let be s 
 *      set of mex out of cycle) mex(s)
 *      of mex(mex(s) union s).
 * 
 *      - I can force this values for one
 *      node in the cycle and verify. 
 *  
 * @complexity O(n \log n) (we can optimize to O(n))
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
vector<int> g[maxn], path;
int vis[maxn];
int c[maxn];
int n;

void get_cycle(int x, vector<int>& cycle) {
    path.push_back(x);
    vis[x] = 1;
    for (int v : g[x]) {
        if (!vis[v]) {
            get_cycle(v, cycle);
        } else if (vis[v] == 1) {
            if (!cycle.empty()) continue;
            for (int i = (int)path.size()-1; i >= 0; --i) {
                cycle.push_back(path[i]);
                if (path[i] == v) break;
            }
            reverse(cycle.begin(), cycle.end());
        }
    }
    vis[x] = 2;
    path.pop_back();
}

pair<int, int> dp(int x) {
    set<int> s;
    vis[x] = 1;
    for (int v : g[x]) {
        if (!vis[v]) dp(v);
        s.insert(c[v]);
    }
    c[x] = 0;
    while (s.count(c[x])) c[x]++;
    pair<int, int> ans = {c[x], c[x] + 1};
    while (s.count(ans.second)) ans.second++;
    return ans;
}

bool check() {
    for (int i = 1; i <= n; ++i) {
        set<int> s;
        for (int v : g[i]) {
            s.insert(c[v]);
        }
        int t = 0;
        while (s.count(t)) t++;
        if (t != c[i]) return 0;
    }
    return 1;
}

void update(int x) {
    set<int> s;
    for (int v : g[x]) {
        s.insert(c[v]);
    }
    c[x] = 0;
    while (s.count(c[x])) c[x]++;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int pi;
        cin >> pi;
        g[pi].push_back(i);
    }   
    vector<int> cycle;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            get_cycle(i, cycle);
        }
    }
    if (cycle.empty()) {
        cout << "POSSIBLE" << endl;
    } else {
        for (int v : cycle) vis[v] = 1;
        memset(c, -1, sizeof c);
        reverse(cycle.begin(), cycle.end());
        memset(vis, 0, sizeof vis);
        vector<pair<int, int>> d;
        for (int v : cycle) {
            d.push_back(dp(v));
        }
        for (int v : {d[0].first, d[0].second}) {
            c[cycle[0]] = v;
            for (int i = 1; i < cycle.size(); ++i) {
                update(cycle[i]);
            }
            if (check()) {
                cout << "POSSIBLE" << endl;
                exit(0);
            }
        }
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}