/**
 * @author Miguel Mini
 * @tag min_queue, prefix_sum
 * @idea
 *      - we can maintain the
 *      set [i-u, i-l] for each
 *      range.
 * 
 *      - if we use a set, we
 *      can perform this in O(\log n)
 *      by query.
 * 
 *      - to better performance 
 *      we can implement a min_queue.
 * 
 *      - a min_queue can be implement 
 *      with two stacks... with
 *      complexity O(1) amortized.
 * 
 * @complexity O(n)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

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

int main() {
	freopen("sum2.in", "r", stdin);
	freopen("sum2.out", "w", stdout);
	int n, l, u;
	scanf("%d%d%d", &n, &l, &u);
	optQueue<int> Q;
	vector<int> sum(n + 1);
	int ans = -2e9;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &sum[i]);
		sum[i] += sum[i-1];
		if (i >= l) Q.add(sum[i-l]);
		if (i >= u+1) Q.pop();
		if (!Q.empty()) ans = max(ans, sum[i] - Q.get());
	}
	printf("%d\n", ans);
	return 0;
}
