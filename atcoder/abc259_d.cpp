#include <bits/stdc++.h>
using namespace std;

const int maxn = 3010;
pair<int, int> p[maxn], d[2];
int r[maxn];
int lnk[maxn];

int get(int x) {
    return x == lnk[x] ? x : lnk[x] = get(lnk[x]);
}

void merge(int x, int y) {
    x = get(x);
    y = get(y);
    lnk[x] = y;
}

int main() {
    int n;
    cin>>n;
    for (int i=0; i<2; ++i) {
        cin>>d[i].first>>d[i].second;
    }
    for (int i=0; i<n; ++i) {
        lnk[i] = i;
    }
    for (int i=0; i<n; ++i) {
        cin>>p[i].first>>p[i].second>>r[i];
        for (int j = 0; j < i; ++j) {
            auto [x1, y1] = p[i];
            auto [x2, y2] = p[j];

            long long dis = (x1 - x2)*1ll*(x1 - x2) + (y1 - y2)*1ll*(y1 - y2);
            if (dis > (r[i] + r[j]) *1ll*(r[i] + r[j])) continue;            
            if (dis >= (r[i] - r[j])*1ll*(r[i] - r[j]))
                merge(i, j); 
        }
    }
    int ids, idt;
    for (int i=0; i<n; ++i) {
        auto [x1, y1] = d[0];
        auto [x2, y2] = d[1];

        auto [cx, cy] = p[i];

        long long d1 = (x1-cx)*1ll*(x1-cx) + (y1-cy)*1ll*(y1-cy);
        if (d1 == r[i]*1ll*r[i]) ids = i;

        long long d2 = (x2-cx)*1ll*(x2-cx) + (y2-cy)*1ll*(y2-cy);
        if (d2 == r[i]*1ll*r[i]) idt = i;
    }
    if (get(ids) == get(idt)) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}