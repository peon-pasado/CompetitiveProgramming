#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w, c, q;
    cin>>h>>w>>c>>q;
    vector<long long> nc(c + 1);
    vector<tuple<int, int, int>> queries; 
    for (int i=0; i<q; ++i) {
        int t, n, c;
        cin>>t>>n>>c;
        queries.emplace_back(t, n, c);
    }
    reverse(queries.begin(), queries.end());
    int rows = h, cols = w;
    set<int> taked_rows, taked_cols;
    for (int i=0; i<q; ++i) {
        auto [t, n, c] = queries[i];
        if (t == 1) {
            if (taked_rows.count(n)) continue;
            taked_rows.insert(n);
            nc[c] += cols;
            rows--;
        } else {
            if (taked_cols.count(n)) continue;
            taked_cols.insert(n);
            nc[c] += rows;
            cols--;
        }
    }
    for (int i=1; i<=c; ++i) {
        cout << nc[i] << " \n"[i==c];
    }
    return 0;
}