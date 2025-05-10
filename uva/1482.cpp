#include <iostream>
using namespace std;

using ll = long long;
ll get(ll x) {
    if (x&1) return get(x/2);
    return x/2;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll r = 0;
        for (int i = 0; i < n; ++i) {
            ll ai;
            cin >> ai;
            r ^= get(ai);
        }
        cout << (r ? "YES" : "NO") << '\n';
    }
    return 0;
}