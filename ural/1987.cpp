#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
pair<pair<int, int>, int> p[MAXN];
int n;
int ans[MAXN];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        p[i] = {{l, r}, i};
    }
    typedef pair<pair<int, int>, int> iii;
    stable_sort(p, p+n, [](iii x, iii y) {return x.first.second - x.first.first < y.first.second - y.first.first;});
    
    int m;
    cin >> m;
    set<pair<int, int>> ss;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        ss.insert({x, i});
    }
    
    for (int i = 0; i < n; ++i) {
        if (ss.empty()) break;
        
        auto lo = ss.lower_bound({p[i].first.first, -1});    
        auto hi = ss.upper_bound({p[i].first.second, m+1});
        
        while (lo != hi) {
            auto q = *lo;
            ans[q.second] = p[i].second + 1;
            ++lo;
        }
        
        auto l = ss.lower_bound({p[i].first.first, -1});    
        auto r = ss.upper_bound({p[i].first.second, m+1});
        while (l != r){
            auto q = l;
            l++;
            ss.erase(q);
        }
    }
    while (not ss.empty()) {
        auto q = ss.begin();
        ans[(*q).second] = -1;
        ss.erase(q);
    }
    
    for (int i = 0; i < m; ++i) printf("%d\n", ans[i]);
    
    return 0;
}