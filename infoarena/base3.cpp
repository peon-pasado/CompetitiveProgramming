/**
 * @author Miguel Mini 
 * @tag dijkstra
 * @idea
 *      - if we use an one in position j
 *      we can represent the problem with
 *      this one in the middle with state:
 *  
 *          (j - 1, len(s) - j)
 * 
 *      - we can reduce states if instead use:
 * 
 *          (x, y) -> (x - min(x, y), y - min(x, y))
 * 
 *      - this states are of the form (0, y) or (x, 0)
 *      with x, y <= max len of a string.
 * 
 *      - we need minimum distance from every
 *      state to state (0, 0).
 * 
 *      - we can reverse the graph and run a  
 *      dijsktra algorithm.
 * 
 *      - the answer is minimum:
 * 
 *          s.size() + dist[node(j-1, len(s)-j)]
 * 
 * @complexity O(sum(s) \log (max(len(s)))) 
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 16010;
using ll = long long;
int O = maxn;
ll dist[2 * maxn + 100];
vector<pair<int, int>> g[2 * maxn + 100];
string s[3];
int d[3];

int get_node(int x, int y) {
    int t = min(x, y);
    x -= t;
    y -= t;
    if (x == 0) return O - y;
    return O + x;
}

void add_edge(int u, int v, int w) {
    g[v].push_back({u, w});
}

void dijkstra(int src) {
    using ii = pair<long long, int>;
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    memset(dist, 1, sizeof dist);
    Q.push({dist[src] = 0, src});
    while (!Q.empty()) {
        auto q = Q.top(); Q.pop();
        if (q.first != dist[q.second]) continue;
        for (auto e : g[q.second]) {
            if (q.first + e.second < dist[e.first]) {
                Q.push({dist[e.first] = q.first + e.second, e.first});
            }
        }
    }
}

int main() {
    freopen("base3.in", "r", stdin);
    freopen("base3.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 3; ++i) {
        cin >> s[i];
        d[i] = s[i].size();
    }
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < 3; ++j) {
            add_edge(get_node(0, i), get_node(d[j], i), d[j]);
            add_edge(get_node(i, 0), get_node(i, d[j]), d[j]);
        }
    }
    dijkstra(get_node(0, 0));
    const ll inf = 5e18;
    ll ans = inf;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < s[i].size(); ++j) {
            if (s[i][j] == '1') {
                int node = get_node(j, (int)s[i].size() - j - 1);
                ans = min(ans, dist[node] + (ll)s[i].size());
            }
        }
    }
    if (ans > 1e15) puts("0");
    else printf("%lld\n", ans);
    return 0;
}