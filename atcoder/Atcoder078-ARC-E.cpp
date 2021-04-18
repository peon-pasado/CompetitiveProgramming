/**
 * @author Miguel Mini
 * @tag constructive, interactive
 * @idea
 *      - if ans = 10^x:
 * 
 *          - query in 10^9 is true
 *          and ans is maximum 5 * x
 *          with true (x = 2 * 10^i).
 * 
 *      - else:
 * 
 *          - query in 10^9 is false
 *          we can obtain number of digits
 *          with query(10^i).
 *          
 *          - in the last step we can
 *          query with 10*x and make a
 *          binary search.
 * 
 * @complexity O(log2(ans) + log10(ans))
 */ 

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
bool query(ll x) {
    cout << "? " << x << endl;
    char c = cin.get();
    while (c < 'N') c = cin.get();
    return c == 'Y';
}

void response(ll x) {
    cout << "! " << x << endl;
}

int main() {
    ll ans = 1e9;
    if (query(ans)) {
        while (ans > 1) {
            if (!query(ans / 5)) break;
            ans /= 10;
        }
        response(ans);
    } else {
        while (ans > 0) {
            ans /= 10;
            if (query(ans)) break;
        }
        ll lo = ans+1, hi = 10*ans-1;
        while (lo < hi) {
            ll mid = lo + (hi-lo)/2;
            if (!query(10 * mid)) lo = mid+1;
            else hi = mid;
        }
        response(lo);
    }
    return 0;
}