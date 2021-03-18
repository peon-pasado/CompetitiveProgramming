/**
 * @author Miguel Mini
 * @tag sorting, number_theory
 * @idea
 *      - we can prove that the pairs
 *      are periodic.
 *
 *      - y is B periodic: (obvious)
 *
 *      - x is AB/gcd(A, B+1) periodic:
 *
 *          - if t1 and t2 have the same pair, then:
 *
 *              t_1 = q_1 B + r
 *              t_2 = q_2 B + r
 *
 *              and:
 *
 *              t_1 + floor(t_1/B) = t_2 + floor(t_2) (mod A)
 *
 *              q_1 B + q_1 = q_2 B + q_2 (mod A)
 *
 *              q_1 (B + 1) = q_2 (B + 1) (mod A)
 *
 *              q_1 = q_2 (mod A / gcd(A, B+1))
 *
 *          therefore:
 *
 *              pairs (x, y) have A / gcd(A, B+1) * B period.
 *
 *       - we can sort and sum intervals.
 *
 * @complexity O(n\log n)
 */

#include <bits/stdc++.h>
using namespace std;

int n;
using ll = long long;
ll A, B;
const ll inf = 5e18;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    scanf("%d%lld%lld", &n, &A, &B);
    long long t = A / gcd(A, B+1);
    t = (t <= (inf + B - 1) / B) ? t * B : inf;
    vector<pair<ll, ll>> v;
    for (int i = 0; i < n; ++i) {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        if (r - l + 1 >= t) v.emplace_back(0, t-1);
        else {
            l %= t; r %= t;
            if (l <= r) v.emplace_back(l, r);
            else {
                v.emplace_back(l, t-1);
                v.emplace_back(0, r);
            }
        }
    }
    sort(v.begin(), v.end());
    ll ans = 0, last = -1;
    for (auto e : v) {
        if (last >= e.second) continue;
        ans += (e.second - max(last, e.first - 1));
        last = e.second;
    }
    printf("%lld\n", ans);
    return 0;
}