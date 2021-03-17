/**
 * @author Miguel Mini
 * @tag sets, manhattan, linear_transform, sorting, bfs, coordinate_compression
 * @idea:
 *      - we can tranaform the plane with:
 *
 *          T(x, y) = (x+y, x-y)
 *
 *      and distance d(p, q) = max(|p.x - q.x|, |p.y - q.y|)
 *
 *      - we can maintain X and Y with sets and delete
 *      the points in every search.
 *
 *      - use dfs or bfs to find the connect component.
 *
 * @complexity: O(n \log n) with big constant
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int x[maxn], y[maxn];
int n;
using ll = long long;
map<ll, int> p1, p2;
bool vis[maxn];
int T;
using vi = vector<int>;
using ii = pair<int, int>;
set<ii> X[maxn];
set<ii> Y[maxn];
vector<int> XX[maxn], YY[maxn];
int deg[maxn];

int main() {
    cin >> n;
    int a, b;
    cin >> a >> b;
    a--; b--;
    for (int i = 0; i < n; ++i) {
        int xi, yi;
        cin >> xi >> yi;
        x[i] = xi+yi;
        y[i] = xi-yi;
        p1[x[i]]; p2[y[i]];
    }
    ll k = max(abs(x[a]-x[b]), abs(y[a]-y[b]));
    int t1 = 0, t2 = 0;
    for (auto& e : p1) e.second = t1++;
    for (auto& e : p2) e.second = t2++;
    for (int i = 0; i < n; ++i) {
        Y[p1[x[i]]].insert({y[i], i}); YY[p1[x[i]]].push_back(y[i]);
        X[p2[y[i]]].insert({x[i], i}); XX[p2[y[i]]].push_back(x[i]);
    }
    for (int i = 0; i < t1; ++i) sort(YY[i].begin(), YY[i].end());
    for (int i = 0; i < t2; ++i) sort(XX[i].begin(), XX[i].end());
    for (int i = 0; i < n; ++i) {
        for (auto d : {-1, 1}) {
            if (p2.count(y[i] + d*k)) {
                int pos = p2[y[i] + d*k];
                deg[i] += upper_bound(XX[pos].begin(), XX[pos].end(), x[i] + k)
                          - lower_bound(XX[pos].begin(), XX[pos].end(), x[i] - k);
            }
            if (p1.count(x[i] + d*k)) {
                int pos = p1[x[i] + d*k];
                deg[i] += upper_bound(YY[pos].begin(), YY[pos].end(), y[i] + (k-1))
                          - lower_bound(YY[pos].begin(), YY[pos].end(), y[i] - (k-1));
            }
        }
    }
    queue<int> Q;
    Q.push(a);
    Q.push(b);
    ll ans = 0;
    while (!Q.empty()) {
        int q = Q.front(); Q.pop();
        vis[q] = 1;
        for (ll d : {-1ll, 1ll}) {
            if (p2.count(y[q] + d*k)) {
                int pos = p2[y[q] + d*k];
                vector<ii> v;
                auto R = X[pos].upper_bound({x[q] + k, maxn});
                for (auto it = X[pos].lower_bound({x[q] - k, -1}); it != R; ++it) {
                    Q.push(it->second);
                    v.push_back(*it);
                }
                for (auto e : v) X[pos].erase(e);
            }
            if (p1.count(x[q] + d*k)) {
                int pos = p1[x[q] + d*k];
                vector<ii> v;
                auto R = Y[pos].upper_bound({y[q] + k-1, maxn});
                for (auto it = Y[pos].lower_bound({y[q] - (k-1), -1}); it != R; ++it) {
                    Q.push(it->second);
                    v.push_back(*it);
                }
                for (auto e : v) Y[pos].erase(e);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (vis[i]) {
            ans += deg[i];
        }
    }
    cout << ans / 2 << endl;
    return 0;
}