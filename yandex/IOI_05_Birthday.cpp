/**
 *  @author Miguel Mini
 *  @tag counting_sort, math, sweep_line 
 *  @idea
 *       - given a direction and rotating k steps,
 *       we can calculate the answer for a boy as:      
 *
 *             a_i = (i - p_i + k)%n
 *             answer_i = min(a_i, n-a_i)  
 *            
 *       - we can also calculate the answer as
 *       the absolute value of a monotic function:
 *
 *            f_i = a_i if a_i <= n/2 else a_i-n
 *            answer_i = abs(f_i)
 *
 *       - update this value to k+1 is simple:
 *
 *            f_i = a_i + 1 if a_i < n/2 else a_i - n
 *
 *        - we can use counting sort to sort 
 *        elements and a deque to "shift" the values.
 *
 *  @complexity: O(n)
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int p[maxn];
int d[maxn];
bool order[maxn];
const int O = maxn / 2;

int solve(int p[], int n) {
    for (int i = 1 - (n+1)/2; i <= n/2; ++i) {
        order[O + i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        d[i] = (p[i] - i + n) % n;
        if (d[i] > n/2) {
            d[i] = d[i] - n;
        }
        order[O + d[i]] = 1;
    }
    deque<int> q;
    for (int i = 1 - (n + 1)/2; i <= n/2; ++i) {
        if (order[O + i]) {
            q.emplace_back(i);
        }
    }
    int ans = 1e9;
    for (int times = 0; times < n; ++times) {
        ans = min(ans, max(abs(q.back() + times), abs(q.front() + times)));
        if (q.back() + times == n/2) {
            q.pop_back();
            q.push_front(1 - (n + 1)/2 - (times + 1));
        }
    }
    return ans;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", p+i);
    }
    int ans = solve(p, n);
    reverse(p+1, p+n+1);
    ans = min(ans, solve(p, n));
    printf("%d\n", ans);
    return 0;
}
