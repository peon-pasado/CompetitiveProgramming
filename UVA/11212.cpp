/**
 * @idea backtracking, heavy pruning
 * 
 * - we can set the answer (pesimistic) to n-1
 *
 * - we can simulate movements and use a lower bound,  
 * that is the number of blocks of consecutive elements
 * divide by two.
 * 
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 12;
int a[maxn];
int n;
int ans;

int heuristic(int a[]) {
    int cnt = 1;
    for (int i=1; i<n; ++i) {
        if (a[i] != a[i-1] + 1) {
            cnt += 1;
        }
    }
    return cnt / 2;
}

void change(int a[], int b[], int i, int j, int len) {
    int m = 0;
    if (i < j) {
        for (int k=0; k<i; ++k) b[m++] = a[k];
        for (int k=i+len; k<=j; ++k) b[m++] = a[k];
        for (int k=i; k<i+len; ++k) b[m++] = a[k];
        for (int k=j+1; k<n; ++k) b[m++] = a[k];
    } else { //j < i
        for (int k=0; k<=j; ++k) b[m++] = a[k];
        for (int k=i; k<i+len; ++k) b[m++] = a[k];
        for (int k=j+1; k<i; ++k) b[m++] = a[k];
        for (int k=i+len; k<n; ++k) b[m++] = a[k];
    }
    assert(m == n);
}

void bt(int depth, int a[]) {
    int h = heuristic(a);
    if (depth + h >= ans) return;
    if (h == 0) {
        ans = min(ans, depth);
        return;
    }
    int b[10];
    for (int i=0; i<n; ++i) {
        for (int len = 1; len <= n - i; ++len) {
            //[i, i+1, ..., i+len-1]
            for (int j=0; j<n; ++j) {
                if (j >= i-1 && j <= i+len-1) continue;
                change(a, b, i, j, len);
                bt(depth+1, b);
            }
        }
    }
}

int main() {
    int tc=1;
    while (cin>>n, n) {
        cout << "Case " << tc++ << ": ";
        for (int i=0; i<n; ++i) {
            cin>>a[i];
        }
        ans = n-1;
        bt(0, a);
        cout << ans << '\n';
    }
    return 0;
}