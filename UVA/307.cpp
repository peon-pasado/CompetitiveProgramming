/**
 * @idea backtracking + pruning
 * 
 * - n <= 60 (hardcoding)
 * 
 * - iterate over divisors.
 * 
 * - build sticke  in order.
 * 
 * - don't repeat elements in a level of backtracking.
 * 
 * - if exist solution, then any elemenet put first is 
 * good.
 * 
 * - if an element is the last too.
 * 
**/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 65;
int n, sum;
int a[maxn];
int L, N;
bool vis[maxn];

bool bt(int pos, int f, int s) {
    if (pos == N) return 1;
    int last = -1;
    for (int i=s; i < n; ++i) {
        if (vis[i] || f + a[i] > L || last == a[i]) continue;
        vis[i] = 1;
        last = a[i];
        if (f + a[i] == L) {
            bool ans = bt(pos+1, 0, 0);
            vis[i] = 0;
            return ans;
        }
        if (bt(pos, f+a[i], i+1)) return 1;
        vis[i] = 0;
        if (f == 0) return 0;
    }   
    return 0;
}

bool check(int len, int num) {
    L = len; N = num;
    memset(vis, 0, sizeof vis);
    return bt(0, 0, 0);
}

int main() {
    while (cin>>n, n) {
        for (int i=0; i<n; ++i) {
            cin>>a[i];
        }
        sort(a, a+n);
        reverse(a, a+n);
        //for (int i=0; i<n; ++i) cout << a[i] << " \n"[i+1==n];
        int sum = accumulate(a, a+n, 0);
        int mx = *max_element(a, a+n);
        int ans = sum;
        for (int i = mx; i < sum; ++i) {
            if (sum % i == 0) {
                if (check(i, sum / i)) {
                    ans = i;
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}