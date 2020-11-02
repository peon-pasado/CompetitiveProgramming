/**
 *  @author Miguel Mini
 *  @tag math, geometry, shebyshev, binary_search
 *  @idea
 *      - use chebyshev tranformation (xi, yi) -> (xi + yi, xi - yi).
 *      - distance manhattan == distance L0 in chebyshev transform.
 *      - we need to locate the elements near the endpoints, we see 
 *        if it is possible to do this with binary search 
 *  @complexity O(N \log N)
**/


#include <bits/stdc++.h>
#include "group.h"
using namespace std;
using ll = long long;

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
   //if (N == 1) return 0;
   for (int i = 0; i < N; ++i) {
        int sum1 = X[i] + Y[i];
        int sum2 = X[i] - Y[i];
        X[i] = sum1;
        Y[i] = sum2;
   }
   ll minx = *min_element(X.begin(), X.end());
   ll maxx = *max_element(X.begin(), X.end());
   ll miny = *min_element(Y.begin(), Y.end());
   ll maxy = *max_element(Y.begin(), Y.end());
   auto p = [&](int k)->bool {
        bool p1 = 1, p2 = 1;
        for (int i = 0; i < N; ++i) {
            bool t1 = X[i] <= minx + k;
            bool t2 = X[i] >= maxx - k;
            bool t3 = Y[i] <= miny + k;
            bool t4 = Y[i] >= maxy - k;
            p1 &= (t1 && t3) || (t2 && t4);
            p2 &= (t1 && t4) || (t2 && t3);
        }
        return p1 || p2;
   };
   int lo = 0, hi = 2e9 + 10;
   while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (!p(mid)) lo = mid+1;
        else hi = mid;
   }
   return lo;
}
