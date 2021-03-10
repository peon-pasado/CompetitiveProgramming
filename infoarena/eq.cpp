/**
 * @author Miguel Mini
 * @tag segment_tree
 * @idea
 *      - we can use a segment tree to maintain
 *      y and z.
 *
 *      - we need:
 *
 *          mx: maximum in range
 *          mn: minimum in range
 *          mxs: maximum sum (a + b)
 *          mns: minimum sum (a + b)
 *          dmx1: maximum difference (a-b)
 *          dmn1: minimum difference (a-b)
 *          dmx2: maximum difference (-a+b)
 *          dmn2: minimum difference (-a+b)
 *
 *      - y = max(left.y,
 *                right.y,
 *                left.mx + max(right.dmx1, right.dmx2),
 *                left.dmx1 + right.mx,
 *                left.mxs - right.mn)
 *      and similar to z.
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
struct Node {
    int mx, mn, y, z, mxs, mns, dmx1, dmn1, dmx2, dmn2;
} st[maxn * 2];
int n, m;

Node merge(Node p, Node q) {
    if (p.mx == -1) return q;
    if (q.mx == -1) return p;
    return {
            max(p.mx, q.mx),
            min(p.mn, q.mn),
            max({p.y, q.y,
                 p.mx + max(q.dmx1, q.dmx2),
                 p.dmx1 + q.mx, p.mxs - q.mn
                }),
            min({p.z, q.z,
                 p.mn + min(q.dmn1, q.dmn2),
                 p.dmn1 + q.mn, p.mns - q.mx
                }),
            max({p.mxs, q.mxs, p.mx + q.mx}),
            min({p.mns, q.mns, p.mn + q.mn}),
            max({p.dmx1, q.dmx1, p.mx - q.mn}),
            min({p.dmn1, q.dmn1, p.mn - q.mx}),
            max({p.dmx2, q.dmx2, -p.mn + q.mx}),
            min({p.dmn2, q.dmn2, -p.mx + q.mn})
    };
}

Node nil;
Node query(int l, int r) {
    Node r1 = nil, r2 = nil;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) r1 = merge(r1, st[l++]);
        if (r&1) r2 = merge(st[--r], r2);
    }
    return merge(r1, r2);
}

int main() {
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);
    nil.mx = -1;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        st[n + i] = {x, x, x, x, 2*x, 2*x, 0, 0, 0, 0};
    }
    for (int i = n-1; i > 0; --i) st[i] = merge(st[i<<1], st[i<<1|1]);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        auto q = query(l-1, r);
        printf("%d\n", q.y + q.z);
    }
    return 0;
}