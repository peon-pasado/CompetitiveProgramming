/**
 *  @author Miguel Mini
 *  @tag dp, constructive, sweep_line, greedy
 *  @idea
 *      - the problem is similar to weighted 
 *      interval scheduling, but in this version
 *      we have many more intervals.
 *
 *      - note that only m + n intervals are needed,
 *      because the intervals thet aren't in place
 *      are indistinguishable.
 *  
 *      - we can do a dp, where the number of
 *      indistinguishable intervals is bounded.
 *
 *      - then we consider our answer only if it
 *      maximize the number of intervals in its
 *      correct position.
 *  
 *      - the rest of intervals are arranged 
 *      so that the total does not exceed n.
 *
 *  @complexity O(nlogn + m) or O(n + m) with adjacent list.
**/

#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int m, l, n;
    cin >> m >> l >> n;
    vector<pair<int, int>> r;
    vector<pair<int, int>> dp(m + 1);
    vector<int> tr(m + 1);
    for (int i = 1; i <= n; ++i) {
        int pos;
        cin >> pos;
        r.push_back({pos + l - 1, i});
    }
    sort(r.begin(), r.end());
    dp[0] = {0, 0};
    tr[0] = -1;
    for (int i = 1, j = 0; i <= m; ++i) {
        while (j + 1 < r.size() && r[j].first == r[j+1].first) j += 1;
        auto& ans = dp[i] = dp[i - 1];
        tr[i] = -1;
        if (i - l >= 0) {
            auto q = dp[i - l];
            int special = q.second;
            int normal = q.first - 2 * special;
            
            if (normal + 1 + special <= n && ans.first < 2 * special + normal + 1) {
                ans.first = 2 * special + normal + 1;
                ans.second = special;
                tr[i] = -2;
            }
            
            if (j < r.size() && r[j].first == i) {
                if (normal + 1 + special <= n) {
                    if (ans.first < 2 * special + normal + 2) {
                        ans.first = 2 * special + normal + 2;
                        ans.second = special + 1;
                        tr[i] = r[j].second;
                    } else if (ans.first == 2 * special + normal + 2 
                                && ans.second < special + 1) {
                        ans.second = special + 1;
                        tr[i] = r[j].second;
                    }
                } else {
                    if (ans.first < n + special + 1) {
                        ans.first = n + special + 1;
                        ans.second = special + 1;
                        tr[i] = r[j].second;
                    } else if (ans.first == n + special + 1 
                                && ans.second < special + 1) {
                        ans.second = special + 1;
                        tr[i] = r[j].second;
                    }
                }
                j += 1;
            }
        }
    }
    int idx = 0;
    for (int i = 1; i <= m; ++i) {
        if (dp[idx].first < dp[i].first) {
            idx = i;
        }
    }
    cout << dp[idx].first << '\n';
    vector<pair<int, int>> res;
    int max_dummy = dp[idx].first - 2 * dp[idx].second;
    vector<bool> vis(n + 1);
    while (idx > 0) {
        if (tr[idx] == -1) {
            idx -= 1;
            continue;
        } 
        if (tr[idx] == -2) {
            if (max_dummy > 0) {
                res.push_back({-1, idx - l + 1});
                max_dummy -= 1;
            }
        } else {
            vis[tr[idx]] = 1;
            res.push_back({tr[idx], idx - l + 1});
        }
        idx -= l;
    }
    vector<int> dis;
    for (int i = 1; i <= n; ++i) if (!vis[i]) dis.push_back(i);
    for (auto& r : res) if (r.first == -1) {
        r.first = dis.back();
        dis.pop_back();
    }
    reverse(res.begin(), res.end());
    cout << res.size() << '\n';
    for (auto r : res) {
        cout << r.first << " " << r.second << '\n';
    }
    return 0;
}
