/**
 * @author Miguel Mini
 * @tag convex_hull, math
 * @idea
 *      - if we use the points (vi, vi * ti)
 *      the combination is the usual sum of
 *      points.
 *
 *      - we need to discard vi from volume
 *      every day.
 *
 *      - we add the i-th volume and keeping
 *      a polyline.
 *
 *      - if current is less hot we need to combine
 *      with the las added.
 *
 *  @complexity O(n)
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l;
    cin >> n >> l;
    using dbl = double;
    using ll = long long;
    vector<dbl> t(n);
    vector<ll> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> v[i];
    }
    deque<int> q;
    int vo = 0;
    dbl vt = 0;
    for (int i = 0; i < n; ++i) {
        int delta = vo + v[i] - l;
        while (!q.empty() && delta > 0) {
            int pos = q.back();
            if (delta >= v[pos]) {
                delta -= v[pos];
                vo -= v[pos];
                vt -= v[pos] * t[pos];
                q.pop_back();
            } else {
                v[pos] -= delta;
                vo -= delta;
                vt -= delta * t[pos];
                delta = 0;
            }
        }
        vt += v[i] * t[i];
        vo += v[i];
        while (!q.empty() && t[q.front()] > t[i]) {
            int pos = q.front();
            t[i] = (t[i] * v[i] + t[pos] * v[pos]) / (v[i] + v[pos]);
            v[i] += v[pos];
            q.pop_front();
        }
        q.push_front(i);
        cout << fixed << setprecision(10);
        cout << vt / l << '\n';
    }
    return 0;
}