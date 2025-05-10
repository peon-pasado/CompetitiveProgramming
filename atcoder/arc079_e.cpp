/**
 * @author Miguel Mini
 * @tag greedy, brute_force
 * @idea
 *      - note that order of
 *      operations is not matter.
 * 
 *      - number of operations is
 *      at most \sum(a_i) * (1/n + 1/n^2 + ...)
 * 
 * @complexity O(\sum \log a_i)
 */ 

#include <bits/stdc++.h>
using namespace std;

int main() {
    int  n;
    cin >> n;
    using ll = long long;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    ll res = 0;
    while (*max_element(a.begin(), a.end()) >= n) {
        for (int i = 0; i < a.size(); ++i) {
            ll q = a[i] / n;
            res += q;
            a[i] %= n;
            for (int j = 0; j < a.size(); ++j) {
                if (i == j) continue;
                a[j] += q;
            }
        }
    }
    cout << res << '\n';
    return 0;
}