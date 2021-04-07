/**
 * @author Miguel Mini
 * @tag number_theory
 * @idea
 *      - we can separate and
 *      find answer to n=b.
 * 
 *      - we need sum i for
 *      integer 2^k * i with
 *      i odd and 2^k * i <= n.
 *  
 *      - number of integers
 *      2^k * i with i odd is:
 *      
 *          floor(n/2^k) - floor(n/2^{k+1})
 * 
 *      - if number of integers
 *      2^k * i is #, answer is #^2.
 * 
 * @complexity O(t \log n)
 */ 
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll get(int n) {
    ll ans = 0;
    for (int i = 29; i >= 0; --i) {
        ll temp = (n>>i) - (n>>i+1);
        ans += temp * temp;
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << get(b) - get(a-1) << '\n';
    }
    return 0;
}