#include <bits/stdc++.h>
using namespace std;

const int maxn = 2.5e7 + 1;   
int perm[maxn];
int inv[maxn];
int x0, a, b, c, d;
int n, m, q;
int L[5001], R[5001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>x0>>a>>b>>c>>d;
    cin>>n>>m>>q;
    iota(perm, perm+n*m, 0);
    int x = x0;
    for (int i=0; i<n*m; ++i) {
        x = ((1ll * a * x + b) % d * x + c) % d; 
        swap(perm[i], perm[x % (i + 1)]);
    }
    while (q--) {
        int i, j;
        cin>>i>>j;
        swap(perm[i-1], perm[j-1]);
    }
    for (int i=0; i<n*m; ++i) {
        inv[perm[i]] = i;
    }
    for (int i=0; i<n; ++i) {
        L[i] = 0; R[i] = m-1;
    }
    vector<int> res;
    for (int i=0; i<n*m; ++i) {
        int x = inv[i] / m;
        int y = inv[i] % m;
        if (L[x] <= y && y <= R[x]) {
            res.emplace_back(i + 1);
            for (int i=0; i<n; ++i) {
                if (i < x) R[i] = min(R[i], y);
                if (x < i) L[i] = max(L[i], y);
            }
        }
    }
    sort(res.begin(), res.end());
    for (int i=0; i<(int)res.size(); ++i) {
        cout << res[i] << " \n"[i+1==(int)res.size()];
    }
    return 0;
}
