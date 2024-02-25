/***
 * @idea backtracking
 * 
 * - n = (sum_{1 \le i \le k} x_i^2) / k-1 
 * - x_i^2 < n  
 * - a_i = n - x_i^2
 * 
 * we can prune with sums (k lowest - k greatest)
**/
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int res[10];
int n, k;
//(l, r]
int sum(int l, int r) {
    return r * (r + 1) * (2*r + 1) / 6 - l * (l + 1) * (2*l + 1) / 6;
}

void bt(int pos, int val, int need) {
    if (pos == k) {
        if (need != 0) return;
        cout << "YES\n";
        for (int i=0; i<k; ++i) {
            cout << res[i] << " \n"[i+1==k];
        } 
        exit(0);
    }
    if (sum(val - k + pos, val) < need) return;
    bt(pos, val-1, need);
    if (sum(0, k - pos - 1) + val*val <= need) {
        res[pos] = n - val*val;
        bt(pos+1, val-1, need - val*val);
    }
}

int main() {
    freopen("squary.in", "r", stdin);
    freopen("squary.out", "w", stdout);
    cin>>n>>k;
    int x = int(sqrt(n - 1));
    bt(0, x, n * (k - 1));
    cout << "NO\n"; 
    return 0;
}