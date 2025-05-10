#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int a[maxn];
int b[maxn];
int p[maxn], sz[maxn];
bool vis[maxn];

int get(int x) {
    return p[x] != x ? p[x] = get(p[x]) : x;
}

void merge(int x, int y) {
    x=get(x); y=get(y);
    if (x==y) return;
    if (sz[x]<sz[y]) swap(x, y);
    sz[x] += sz[y];
    p[y] = x;
}

int main() {
    int n;
    cin>>n;
    vector<pair<int, int>> ai;
    for (int i=0; i<n; ++i) {
        cin>>a[i];
        ai.push_back({a[i], i});
    }
    sort(ai.rbegin(), ai.rend());
    int ss = 0;
    for (int i=0; i<n; ++i) {
        int j = i;
        while (j + 1 < n && ai[j].first == ai[j+1].first) {
            j += 1;
        }
        for (int k = i; k <= j; ++k) {
            int pos = ai[k].second;
            vis[pos] = 1;
            sz[pos] = 1;
            p[pos] = pos;
            if (pos - 1 >= 0 && vis[pos - 1]) merge(pos-1, pos);
            if (pos + 1 < n && vis[pos + 1]) merge(pos+1, pos); 
            ss = max(ss, sz[get(pos)]); 
        }
        b[ss] = max(b[ss], ai[i].first);
        i = j;
    }
    for (int i=n-1; i>=1; --i) {
        b[i] = max(b[i], b[i+1]);
    }
    for (int i=1; i<=n; ++i) cout << b[i] << " \n"[i==n];
    return 0;
}