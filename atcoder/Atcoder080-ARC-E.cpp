/**
 * @author Miguel Mini
 * @tag segment_tree, greedy
 * @idea
 *      - we can notice that first 
 *      position and second position
 *      make a parenthesis balance.
 * 
 *      - to fix first element we 
 *      can force any element in even
 *      position and second element
 *      in odd position to right.
 * 
 *      - note that ranges cant 
 *      contribute to same pair.
 * 
 *      - we can use a priority queue
 *      to obtain best pair and segment
 *      tree to find these in a range.
 * 
 * @complexity O(n\log n)
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
struct Node {
    int sum;
    int e, o;
} st[maxn << 2];
int n;
int a[maxn];
const int inf = 2e9;

Node merge(Node p, Node q) {
    Node ans = p;
    if (p.sum&1) {
        if (a[p.e] > a[q.o]) ans.e=q.o;
        if (a[p.o] > a[q.e]) ans.o=q.e;
    } else {
        if (a[p.e] > a[q.e]) ans.e=q.e;
        if (a[p.o] > a[q.o]) ans.o=q.o;
    }
    ans.sum = p.sum+q.sum;
    return ans;
}

void build(int nx=1, int l=0, int r=n-1) {
    if (l == r){ 
        st[nx] = {1, r, n};
        return;
    }
    int mid = (l+r)/2;
    build(nx<<1, l, mid);
    build(nx<<1|1, mid+1, r);
    st[nx] = merge(st[nx<<1], st[nx<<1|1]);
}

Node query(int ll, int rr, int nx=1, int l=0, int r=n-1) {
    if (r < ll || rr < l) return {0, n, n};
    if (ll <= l && r <= rr) return st[nx];
    int mid = (l+r)/2;
    return merge(query(ll, rr, nx<<1, l, mid), 
                    query(ll, rr, nx<<1|1, mid+1, r));
}

int main() {
    cin >> n;
    a[n] = inf;
    for (int i = 0; i < n; ++i) cin >> a[i];
    build();
    using iii = pair<int, pair<int, int>>;  
    priority_queue<iii, vector<iii>, greater<iii>> Q;
    Q.push({a[st[1].e], {0, n-1}});
    for (int i = 0; i < n / 2; ++i) {
        auto range = Q.top().second; Q.pop();
        auto q = query(range.first, range.second);
        q = query(q.e, range.second);
        cout << a[q.e] << " " << a[q.o] << " ";
        if (range.first != q.e) Q.push({a[query(range.first, q.e-1).e], {range.first, q.e-1}});
        if (q.e + 1 < q.o) Q.push({a[query(q.e+1, q.o-1).e], {q.e+1, q.o-1}});
        if (q.o != range.second) Q.push({a[query(q.o+1, range.second).e], {q.o+1, range.second}});
    }   
    return 0;
}