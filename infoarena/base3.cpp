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
int dist[maxn];
vector<pair<int, int>> g[maxn];
string s[3];

void dijkstra(int src) {
    using ii = pair<int, int>;
    priority_queue<ii, vector<ii>, greater<ii>> Q;
    for (int i = 1; i < maxn; ++i) dist[i] = 2e9;
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
    for (int i = 0; i < 3; ++i) cin >> s[i];
    for (int i = 0; i < 3; ++i) {
        int m = s[i].size();
        for (int j = 0; j < maxn; ++j) {
            g[abs(m - j)].emplace_back(j, m);
        }
    }
    dijkstra(0);
    int ans = 2e9;
    for (int i = 0; i < 3; ++i) {
        int m = s[i].size();
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '1') {
                ans = min(ans, dist[abs(m - 2 * j - 1)] + m);
            }
        }
    }
    if (ans > 1e9) puts("0");
    else printf("%d\n", ans);
    return 0;
}