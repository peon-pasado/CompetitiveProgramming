/**
 * @author Miguel Mini
 * @tag BST, lazy_propagation
 * @idea:
 *      - if we can modify operation
 *      i, and current distance is d
 *      then we can get any d in range
 *      [0, d].
 *
 *      - if we apply operation i to
 *      range [0, x] then the new range
 *      is: [0, max(x-d_i, min(x, d_i/2))]
 *
 *      - if we define f_i(x) as the
 *      operation of applying the operation
 *      i to the range [0, x].
 *
 *      - f_i(x) maintains non-decreasing
 *      functions.
 *
 *      - another way to express f_i is:
 *
 *                { x         if x < d_i / 2
 *      f_i(x) =  { d_i / 2   if d_i / 2 <= x <= d_i + d_i / 2
 *                { x - d_i   if d_i + d_i / 2 < x
 *
 *      - we can maintain this operation with
 *      a bst (treap, splay tree) and lazy propagation.
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<> dis(1, 2e9);

struct Node {
    int k, pr, id;
    int l, r;
    int cnt;
    int set, inc;
    Node() {}
    Node(int v, int i):
            k(v), id(i), pr(dis(rng)),
            l(0), r(0), cnt(1),
            set(-1), inc(0) {}
} T[maxn];
int elm = 0;

int cnt(int t) {
    return t ? T[t].cnt : 0;
}

void upd(int t) {
    if (t)
        T[t].cnt = cnt(T[t].l) + 1 + cnt(T[t].r);
}

void push(int t) {
    if (t) {
        if (~T[t].set) T[t].k = T[t].set;
        T[t].k += T[t].inc;
        for (int v : {T[t].l, T[t].r}) {
            if (v) {
                if (~T[t].set) {
                    T[v].set = T[t].set;
                    T[v].inc = T[t].inc;
                } else {
                    T[v].inc += T[t].inc;
                }
            }
        }
        T[t].set = -1; T[t].inc = 0;
    }
}

void merge(int& t, int l, int r) {
    push(l); push(r);
    if (!l || !r) t=l^r;
    else if (T[l].pr>T[r].pr) merge(T[l].r, T[l].r, r), t=l;
    else merge(T[r].l, l, T[r].l), t=r;
    upd(t);
}

void split(int t, int& l, int& r, int k) { //[...key)[key...]
    push(t);
    if (!t) return void(l=r=0);
    if (T[t].k < k) split(T[t].r, T[t].r, r, k), l=t;
    else split(T[t].l, l, T[t].l, k), r=t;
    upd(t);
}

void add(int& t, int v, int id) {
    int x;
    split(t, t, x, v);
    T[++elm] = Node(v, id);
    merge(x, elm, x);
    merge(t, t, x);
}

void update(int& t, int d) {
    int l = d/2, r = d + d/2;
    int x, y;
    split(t, t, x, l);
    split(x, x, y, r + 1);
    if (x) {
        T[x].set = d/2;
        T[x].inc = 0;
    }
    merge(t, t, x);
    if (y) {
        T[y].set = -1;
        T[y].inc = -d;
    }
    merge(t, t, y);
}

int ans[maxn];
void dfs(int x) {
    if (!x) return;
    push(x);
    ans[T[x].id] = T[x].k;
    dfs(T[x].l); dfs(T[x].r);
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        update(root, x);
        add(root, d, i);
        d = min(d, abs(d-x));
    }
    dfs(root);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        int x;
        scanf("%d", &x);
        puts(ans[x] ? "YES" : "NO");
    }
    return 0;
}