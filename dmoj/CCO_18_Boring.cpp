/**
 * @author Miguel Mini
 * @tag monotone_queue, sqrt_decomposition, sorting
 * @idea
 *      - use sqrt decomposition over queries
 *
 *      - divide in sqrt(n) blocks and maintain
 *      next sqrt(n) change positions.
 *
 *      - solve the problem without change positions
 *      with monotone queue...
 *
 *      - solve problem with monotone queue 
 *      for query with change positions.
 *
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
const int maxq = 1e5 + 10;
int n, k, q;
int a[maxn];
struct Query {
    int i, x;
} qu[maxq];
int res;
int l[maxn], r[maxn];

template <class T, class compare=less<T>>
struct optQueue {
    stack<T> l, r;
    T best;
    optQueue() {}
    T f(T x, T y) {
      return compare()(x, y) ? x : y;
    }
    void add(T c) {
      best = r.empty() ? c : f(best, c);
      r.push(c);
    }
    bool empty() {
      return l.empty() && r.empty();
    }
    size_t size() {
      return l.size() + r.size();
    }
    void pop() {
      assert(!empty());
      if (l.empty()) {
        while (!r.empty()) {
          if (l.empty()) l.push(r.top());
          else l.push(f(l.top(), r.top()));
          r.pop();
        }
      }
      l.pop();
    }
    T get() {
      assert(!empty());
      if (l.empty()) return best;
      if (r.empty()) return l.top();
      return f(l.top(), best);
    }
};

bool vis[maxn];
const int inf = 1.2e9;
void build(int ll, int rr) {
    optQueue<int, greater<int>> Ql, Qr;
    memset(vis, 0, sizeof vis);
    for (int i = ll; i <= rr; ++i) {
        vis[qu[i].i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (i >= k) Ql.pop();
        if (!Ql.empty()) l[i] = Ql.get();
        else l[i] = -inf;
        Ql.add(vis[i] ? -inf : a[i]);
    }
    for (int i = n-1; i >= 0; --i) {
        if (n-1-i >= k) Qr.pop();
        if (!Qr.empty()) r[i] = Qr.get();
        else r[i] = -inf;
        Qr.add(vis[i] ? -inf : a[i]);
    }
    res = -inf;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            res = max(res, max(l[i], r[i]) + a[i]);
        }
    }
}

struct cmp {
    bool operator()(int i, int j) {
        return a[i] > a[j]; 
    }
};

int main() {
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 0; i < n; ++i) scanf("%d", a+i);
    qu[0] = {0, a[0]};
    for (int i = 1; i <= q; ++i) {
        int id, x;
        scanf("%d%d", &id, &x);
        qu[i] = {id - 1, x};
    }
    q += 1;
    //6b +  6n/b
    int sq = sqrt(n) + 1;
    vector<int> Q;
    for (int i = 0; i < q; ++i) {
        if (i % sq == 0) {
            build(i, min(q-1, i + sq - 1));
            Q.clear();
            for (int j = i; j < min(q, i+sq); ++j) {
                Q.push_back(qu[j].i);
            }
            sort(Q.begin(), Q.end());
            Q.resize(unique(Q.begin(), Q.end()) - Q.begin());
        }
        a[qu[i].i] = qu[i].x;
        int ans = res;
        deque<int> lQ, rQ;
        for (int j = 0; j < Q.size(); ++j) {
            int id = Q[j];
            ans = max(ans, max(l[id], r[id]) + a[id]);
            while (!lQ.empty() && id - lQ.front() >= k) lQ.pop_front();
            while (!lQ.empty() && a[lQ.back()] < a[id]) lQ.pop_back();
            if (!lQ.empty()) {
                ans = max(ans, a[lQ.front()] + a[id]);
            }
            lQ.push_back(id);
        }
        for (int j = (int)Q.size() - 1; j >= 0; --j) {
            int id = Q[j];
            while (!rQ.empty() && rQ.front() - id >= k) rQ.pop_front();
            while (!rQ.empty() && a[rQ.back()] < a[id]) rQ.pop_back();
            if (!rQ.empty()) {
                ans = max(ans, a[rQ.front()] + a[id]);
            }
            rQ.push_back(id);
        }
        printf("%d\n", ans);
    }
    return 0;
}
