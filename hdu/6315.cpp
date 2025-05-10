#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int b[maxn];
struct Node {
    int min_b;
    int sum;    
} st[4*maxn];
int lazy[4*maxn];
int n, q;

void upd_one(int nx, int k) {
    st[nx].min_b -= k;
    lazy[nx] += k;
}

void push(int nx) {
    if (lazy[nx]) {
        upd_one(2*nx, lazy[nx]);
        upd_one(2*nx+1, lazy[nx]);
        lazy[nx] = 0;       
    }
}

Node merge(const Node& p, const Node& q) {
    return {min(p.min_b, q.min_b), p.sum + q.sum};
}

void build(int nx=1, int l=1, int r=n) {
    lazy[nx] = 0;
    if (l == r) {
        st[nx] = {b[r], 0};
        return;
    }
    int mid=(l+r)/2;
    build(2*nx, l, mid);
    build(2*nx+1, mid+1, r);
    st[nx] = merge(st[nx*2], st[nx*2+1]);
}

int query(int ll, int rr, int nx=1, int l=1, int r=n) {
    if (rr < l || r < ll) return 0;
    if (ll <= l && r <= rr) return st[nx].sum;
    push(nx);
    int mid=(l+r)/2;
    return  query(ll, rr, 2*nx, l, mid) + query(ll, rr, 2*nx+1, mid+1, r);
}

void update(int ll, int rr, int nx=1, int l=1, int r=n) {
    if (rr < l || r < ll) return;
    if (ll <= l && r <= rr && st[nx].min_b > 1) return upd_one(nx, 1);
    if (l == r) {
        st[nx].min_b--;
        int k = b[r] - st[nx].min_b;
        st[nx].sum += k / b[r];
        st[nx].min_b = b[r] - k % b[r];
        return;
    }
    push(nx);
    int mid=(l+r)/2;
    update(ll, rr, 2*nx, l, mid);
    update(ll, rr, 2*nx+1, mid+1, r); 
    st[nx] = merge(st[2*nx], st[2*nx+1]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin>>n>>q) {
        for (int i=1; i<=n; ++i) cin>>b[i];
        build();
        while (q--) {
            string type;
            int l, r;
            cin>>type>>l>>r;
            if (type[0] == 'a') update(l, r);
            else {
                cout << query(l, r) << '\n';
            }
        }
    }
    return 0;
}