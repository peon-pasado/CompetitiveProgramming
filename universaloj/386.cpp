#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int64_t inf = 1e18;
int n, m, ds, dv;
pair<int, int> p[maxn];
int nxt[maxn], bck[maxn];

int64_t ans;
void upd(int64_t x, int64_t y) {
    if (dv == 2) x *= x;
    if (ds == 2) y *= y;
    ans = max(ans, x - y);
}

int main() {
    cin>>n>>m>>ds>>dv;
    for (int i=0; i<n; ++i) {
        cin>>p[i].first>>p[i].second; //first is unique
    }
    sort(p, p+n);
    for (int i=0; i<n; ++i) {
        int64_t sx=0;
        for (int j=0; j<m && i+j<n; ++j) {
            sx += p[i+j].second;
            upd(sx, p[i+j].first - p[i].first);
        }
    }
    for (int i=0; i<n; ++i) {
        nxt[i] = i+1;
        bck[i] = i-1;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j) {
        return p[i].second < p[j].second;
    });
    for (int i : id) {
        vector<int> vs;
        for (int j=bck[i]; j!=-1; j = bck[j]) {
            vs.push_back(j);
            if (vs.size() == m - 1) break;
        }
        reverse(vs.begin(), vs.end());
        int t = vs.size();
        for (int j=i; j!=n; j = nxt[j]) {
            vs.push_back(j);
            if (vs.size() == t + m) break;
        }
        vector<int64_t> sx(vs.size());
        sx[0] = p[vs[0]].second;
        for (int i=1; i<vs.size(); ++i) {
            sx[i] = sx[i-1] + p[vs[i]].second;
        }
        for (int i=m-1; i<sx.size(); ++i) {
            upd(sx[i] - (i == m-1?0:sx[i-m]), p[vs[i]].first - p[vs[i-m+1]].first);
        }
        if (bck[i] != -1) nxt[bck[i]] = nxt[i];
        if (nxt[i] != n) bck[nxt[i]] = bck[i];
    }
    cout << ans << '\n';
    return 0;
}