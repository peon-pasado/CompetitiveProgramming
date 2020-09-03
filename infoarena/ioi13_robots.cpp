/**
 * @author Miguel Mini
 * @tag greedy, sweep_line, priority_queue
 * @idea
 *      - we can use binary search (fix the answer)
 * 
 *      - If we go from light to heavy weight, we can
 *      take in each step those less than an X_i, but 
 *      before that we put it in a priority_queue that 
 *      orders them from largest to smallest according 
 *      to their size.
 * 
 *      - finally sort size and we greedily take these.
 * 
 * @complexity O(Tlog^2T)
**/

#include <bits/stdc++.h>
#include"robots.h"
using namespace std;

const int maxn = 1e6 + 10;
int ind[maxn];

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    for (int i=0; i<T; ++i) ind[i] = i;
    sort(ind, ind+T, [&](int p, int q) {
       return W[p] < W[q]; 
    });
    sort(X, X+A);
    sort(Y, Y+B);
    auto f = [&](int x) {
        priority_queue<int> q;
        int j=0;
        for (int i=0; i<A; ++i) {
            while (j < T && W[ind[j]] < X[i]) {
               q.push(S[ind[j]]);
               j += 1;
            }
            for (int k=0; k<x && !q.empty(); ++k) q.pop();
        }
        priority_queue<int, vector<int>, greater<int>> p;
        while (j < T) p.push(S[ind[j++]]);
        while (!q.empty()) p.push(q.top()), q.pop();
        for (int i=0; i<B; ++i) {
            for (int k=0; k<x && !p.empty(); ++k) {
                if (p.top() < Y[i]) p.pop();
                else break;
            }
        }
        return p.empty();
    };
    int lo = 1, hi = T;
    while (lo < hi) {
        int mid = lo+(hi-lo)/2;
        if (!f(mid)) lo = mid+1;
        else hi=mid;
    }
    if (!f(lo)) return -1;
    return lo;
}

/**
int X[maxn], Y[maxn], W[maxn], S[maxn];

int main() {
    int A, B, T;
    scanf("%d%d%d", &A, &B, &T);
    for (int i=0; i<A; ++i) scanf("%d", X+i);
    for (int i=0; i<B; ++i) scanf("%d", Y+i);
    for (int i=0; i<T; ++i) scanf("%d%d", W+i, S+i);
    printf("%d\n", putaway(A, B, T, X, Y, W, S));
	return 0;
}
**/
