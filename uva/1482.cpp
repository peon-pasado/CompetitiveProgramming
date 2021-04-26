/**
 * @author Miguel Mini
 * @tag grundy_number, pattern
 * @idea
 * 
 *  - simple:
 * 
 *      - we can print grundy function
 *      and notice that:
 * 
 *          G(2k) = k
 *          G(2k+1) = G(k)
 * 
 *   - complex:
 * 
 *      - if G(k) = 0 then G(2k+1) = 0.
 *      and min(G([k+1, 2k])) > 0.
 * 
 *      - we have:
 * 
 *          G(2^k - 1) = 0.
 * 
 *      - set(G([2^k+1, 2^{k+1}])) = {0, 1, ..., 2^k}
 * 
 *      remark: we can notice that first half is 
 *      G(2^k + 2*i + 1) = G(2^{k-1} + i) (simule).
 *      and G(2^k + 2*i) = 2^{k-1} + i (this elements are new).
 * 
 * @complexity O(t * n)
 */ 

#include <iostream>
using namespace std;

using ll = long long;
ll get(ll x) {
    //if (x&1) return get(x/2);
    //return x/2;
    return x >> (__builtin_ctzll(~x) + 1);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll r = 0;
        for (int i = 0; i < n; ++i) {
            ll ai;
            cin >> ai;
            r ^= get(ai);
        }
        cout << (r ? "YES" : "NO") << '\n';
    }
    return 0;
}