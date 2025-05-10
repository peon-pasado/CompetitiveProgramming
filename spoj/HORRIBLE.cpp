#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10; 
int arr[maxn];
using ll = long long;
ll st[maxn * 4];
ll lazy_value[maxn * 4];

void build(int nodo, int l, int r) {
    lazy_value[nodo] = 0;
    if (l == r) {
        st[nodo] = arr[r];
        return;
    }
    int mid = (l+r)/2;
    build(2 * nodo, l, mid);
    build(2 * nodo + 1, mid+1, r); 
    st[nodo] = st[2 * nodo] + st[2 * nodo + 1];
}

void update_include(int nodo, ll x, int l, int r) {
    st[nodo] += (r - l + 1) *1ll* x;
    lazy_value[nodo] += x;
}

void push(int nodo, int l, int r) {
    if (lazy_value[nodo]) {
        int mid = (l + r) / 2;
        update_include(2 * nodo, lazy_value[nodo], l, mid);
        update_include(2 * nodo + 1, lazy_value[nodo], mid+1, r);
        lazy_value[nodo] = 0;
    }
}

void update(int ll, int rr, int x, int nodo, int l, int r) {
    if (rr < l || r < ll) return;
    if (ll <= l && r <= rr) {
        update_include(nodo, x, l, r);
        return;
    }
    push(nodo, l, r);
    int mid = (l + r) / 2;
    update(ll, rr, x, 2 * nodo, l, mid);
    update(ll, rr, x, 2 * nodo + 1, mid+1, r);
    st[nodo] = st[2 * nodo] + st[2 * nodo + 1];
}

ll query(int ll1, int rr, int nodo, int l, int r) {
    if (rr < l || r < ll1) return 0;
    if (ll1 <= l && r <= rr) return st[nodo];
    push(nodo, l, r);
    int mid = (l + r) / 2;
    ll L = query(ll1, rr, 2 * nodo, l, mid);
    ll R = query(ll1, rr, 2 * nodo + 1, mid+1, r);
    return L + R;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n, c;
        cin>>n>>c;
        build(1, 1, n);
        while (c--) {
            int type;
            cin>>type;
            if (type) {
                int l, r;
                cin>>l>>r;
                if (r < l) swap(l, r);
                cout << query(l, r, 1, 1, n) << '\n';
            } else {
                int l, r, v;
                cin>>l>>r>>v;
                if (r < l) swap(l, r);
                update(l, r, v, 1, 1, n);
            }
        }
    }
    return 0;
}   