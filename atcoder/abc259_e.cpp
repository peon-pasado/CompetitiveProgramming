#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> d(n);
    vector<int> X, Y;
    for (int i=0; i<n; ++i) {
        int m;
        cin>>m;
        for (int j=0; j<m; ++j) {
            int x, y;
            cin>>x>>y;
            X.push_back(x);
            Y.push_back(y);
            d[i].push_back({x, y});
        }
    }   
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    vector<pair<int, int>> cnt(X.size(), {-1, -1});
    for (int i=0; i<n; ++i) {
        for (int j = 0; j < d[i].size(); ++j) {
            d[i][j].first = lower_bound(X.begin(), X.end(), d[i][j].first) - X.begin();
            d[i][j].second = lower_bound(Y.begin(), Y.end(), d[i][j].second) - Y.begin();
        
            if (d[i][j].second > cnt[d[i][j].first].first) {
                cnt[d[i][j].first] = {d[i][j].second, 1};
            } else if (d[i][j].second == cnt[d[i][j].first].first) {
                cnt[d[i][j].first].second++;
            }
        }
    }

    int res = 0;
    bool extra = 0;
    for (int i=0; i<n; ++i) {
        bool ok = 0;
        for (int j = 0; j < d[i].size(); ++j) {
            if (cnt[d[i][j].first].first == d[i][j].second) {
                ok |= cnt[d[i][j].first].second == 1;
            }
        }
        res += ok;
        if (!ok) extra = 1;
    }
    cout << res + extra << '\n';
    return 0;
}