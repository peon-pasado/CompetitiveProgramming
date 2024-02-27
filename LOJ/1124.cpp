/**
 * @idea backtacking, PIE, combinatorics
 * 
 * - the equation is:
 * 
 *      sum xi = n
 * 
 *  s.t. li <= xi <= ri, for all i
 * 
 * 
 * - is the same that:
 * 
 *      sum ti = n - (sum li) = n'
 * 
 *  s.t. 0 <= ti <= ri - li
 * 
 * - we can use PIE over constraints 
 * and we can count if we take a constraint
 * or not.
 * 
 * @complexity O(2^k * k) or O(2^k) 
**/

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e8 + 7;
int r[12];
int k, n;

int add(int a, int b) {
    return a + b >= mod ? a + b - mod : a + b;
}

int mul(long long a, long long b) {
    return a * b % mod;
}

int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

int comb(int n, int m) {
    if (m > n) return 0;
    int ans = 1; 
    for (int i=0; i<m; ++i) {
        ans = mul(ans, n - i);
        ans = mul(ans, ex(i + 1, mod - 2));
    }
    return ans;
}

int bt(int pos, int sum) {
    if (pos == k) return comb(n - sum + k - 1, k - 1);
    return add(bt(pos+1, sum), mod - bt(pos+1, sum + r[pos] + 1));
}

int main() {
    int t;
    cin>>t;
    int tc = 1;
    while (t--) {
        cin>>k>>n;
        for (int i=0; i<k; ++i) {
            int x, y;
            cin>>x>>y;
            n -= x;
            r[i] = y - x;
        }
        cout << "Case " << tc++ << ": " << bt(0, 0) << '\n';
    }
    return 0;
}