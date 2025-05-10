#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
int ft[maxn];

void upd(int pos) {
    while (pos < maxn) {
        ft[pos] += 1;
        pos += pos&-pos;
    }
}

int query(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += ft[pos];
        pos -= pos&-pos;
    }
    return ans;
}
using ll = long long;

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        ll ans = 0;
        memset(ft, 0, sizeof ft);
        for (int i = 0; i < n; ++i) {
            int x;
            cin>>x;
            ans += query(x);
            upd(x);
        }
        cout << ans << '\n';
    }
    return 0;
}