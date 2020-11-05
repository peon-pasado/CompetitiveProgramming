/**
 *  @author Miguel Mini
 *  @tag binary_search, dp, brute_force
 *  @idea
 *      - force the minimum element set
 *      and use binary search in the answer      
 *
 *      - every element has at least a corner.
 *    
 *      - we can extend from a corner
 *      the set containing the minimum (with binary search).
 *
 *  @complexity O(n^2 + nlog^2n)
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2010;
int a[maxn][maxn];
int L[maxn][maxn][2];
int R[maxn][maxn][2];
int D[maxn][maxn][2];
int U[maxn][maxn][2];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int mn = 1e9, mx = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", a[i]+j);
            mn = min(mn, a[i][j]);
            mx = max(mx, a[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        L[i][0][0] = L[i][0][1] = a[i][0];
        for (int j = 1; j < m; ++j) {
            L[i][j][0] = min(L[i][j-1][0], a[i][j]);
            L[i][j][1] = max(L[i][j-1][1], a[i][j]);
        }
        R[i][m-1][0] = R[i][m-1][1] = a[i][m-1];
        for (int j = m-2; j >= 0; --j) {
            R[i][j][0] = min(R[i][j+1][0], a[i][j]);
            R[i][j][1] = max(R[i][j+1][1], a[i][j]);
        }
    }
    for (int j = 0; j < m; ++j) {
        U[0][j][0] = U[0][j][1] = a[0][j];
        for (int i = 1; i < n; ++i) {
            U[i][j][0] = min(U[i-1][j][0], a[i][j]);
            U[i][j][1] = max(U[i-1][j][1], a[i][j]);
        }
        D[n-1][j][0] = D[n-1][j][1] = a[n-1][j];
        for (int i = n-2; i >= 0; --i) {
            D[i][j][0] = min(D[i+1][j][0], a[i][j]);
            D[i][j][1] = max(D[i+1][j][1], a[i][j]);
        }
    }
    auto getL = [&](int x)->bool {
        int mi = 1e9, ma = 1, t;
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            int lo = 0, hi = m-1;
            while (lo < hi) {
                int mid = lo + (hi-lo+1) / 2;
                if (L[i][mid][1] - mn <= x) lo = mid;
                else hi = mid-1;
            }
            if (L[i][lo][1] - mn > x) lo -= 1;
            res[i] = lo;
        }
        mi = 1e9, ma = 1, t = m-1;
        for (int i = 0; i < n; ++i) {
            t = min(t, res[i]);
            if (t + 1 < m) {
                mi = min(mi, R[i][t+1][0]);
                ma = max(ma, R[i][t+1][1]);
            }
        }
        if (ma - mi <= x) return 1;
        mi = 1e9, ma = 1, t = m-1;
        for (int i = n-1; i >= 0; --i) {
            t = min(t, res[i]);
            if (t + 1 < m) {
                mi = min(mi, R[i][t+1][0]);
                ma = max(ma, R[i][t+1][1]);
            }
        }
        return ma - mi <= x;
    };
    auto getR = [&](int x)->bool {
        int mi = 1e9, ma = 1, t;
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            int lo = 0, hi = m-1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (R[i][mid][1] - mn > x) lo = mid+1;
                else hi = mid;
            }
            if (R[i][lo][1] - mn > x) lo += 1;
            res[i] = lo;
        }
        mi = 1e9, ma = 1, t = 0;
        for (int i = 0; i < n; ++i) {
            t = max(t, res[i]);
            if (t > 0) {
                mi = min(mi, L[i][t-1][0]);
                ma = max(ma, L[i][t-1][1]);
            }
        }
        if (ma - mi <= x) return 1;
        mi = 1e9, ma = 1, t = 0;
        for (int i = n-1; i >= 0; --i) {
            t = max(t, res[i]);
            if (t > 0) {
                mi = min(mi, L[i][t-1][0]);
                ma = max(ma, L[i][t-1][1]);
            }
        }
        return ma - mi <= x;
    };
    auto getU = [&](int x)->bool {
        int mi = 1e9, ma = 1, t;
        vector<int> res(m);
        for (int i = 0; i < m; ++i) {
            int lo = 0, hi = n-1;
            while (lo < hi) {
                int mid = lo + (hi - lo + 1) / 2;
                if (U[mid][i][1] - mn <= x) lo = mid;
                else hi = mid-1;
            }
            if (U[lo][i][1] - mn > x) lo -= 1; 
            res[i] = lo;
        }
        mi = 1e9, ma = 1, t = n-1;
        for (int i = 0; i < m; ++i) {
            t = min(t, res[i]);
            if (t + 1 < n) {
                mi = min(mi, D[t+1][i][0]);
                ma = max(ma, D[t+1][i][1]);
            }
        }
        if (ma - mi <= x) return 1;
        mi = 1e9, ma = 1, t = n-1;
        for (int i = m-1; i >= 0; --i) {
            t = min(t, res[i]);
            if (t + 1 < n) {
                mi = min(mi, D[t+1][i][0]);
                ma = max(ma, D[t+1][i][1]);
            }
        }
        return ma - mi <= x;   
    };
    auto getD = [&](int x)->bool {
        int mi = 1e9, ma = 1, t;
        vector<int> res(m);
        for (int i = 0; i < m; ++i) {
            int lo = 0, hi = n-1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (D[mid][i][1] - mn > x) lo = mid+1;
                else hi = mid;
            }
            if (D[lo][i][1] - mn > x) lo += 1;
            res[i] = lo;
        }
        mi = 1e9, ma = 1, t = 0;
        for (int i = 0; i < m; ++i) {
            t = max(t, res[i]);
            if (t > 0) {
                mi = min(mi, U[t-1][i][0]);
                ma = max(ma, U[t-1][i][1]);
            }
        }
        if (ma - mi <= x) return 1;
        mi = 1e9, ma = 1, t = 0;
        for (int i = m-1; i >= 0; --i) {
            t = max(t, res[i]);
            if (t > 0) {
                mi = min(mi, U[t-1][i][0]);
                ma = max(ma, U[t-1][i][1]);
            }
        }
        return ma - mi <= x;   
    };
    auto p = [&](int x) {
        if (getL(x)) return 1;
        if (getR(x)) return 1;
        if (getD(x)) return 1;
        if (getU(x)) return 1;
        return 0;
    };
    int lo = 0, hi = mx - mn;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (!p(mid)) lo = mid+1;
        else hi = mid;
    }
    printf("%d\n", lo);
    return 0;
}
