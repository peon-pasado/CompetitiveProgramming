/**
 * @author Miguel Mini
 * @tag math, probability, two_pointers
 * @idea
 *      - probability in a range [l, r] is
 *
 *      pl * (1-pl+1) * (1-pl+2) *...* (1-pr)
 *      + (1-pl) * (pl+1) * (1-pl+2) *...* (1-pr)
 *      ...
 *      + (1-pl) *...* pr
 *
 *      = (1-pl)*(1-pl+1)*...*(1-pr) * (pl/(1-pl) + pl+1/(1-pl+1) + ... + pr/(1-pr))
 *
 *      = PROD * (sum pi / (1 - pi))
 *
 *      = PROD * SUM
 *
 *      - if add a new p' we obtain:
 *
 *          PROD * (1 - p') * (SUM + p' / (1 - p'))
 *
 *          PROD * SUM * (1 - p') + PROD * p'
 *
 *      - if PROD * SUM * (1 - p') + PROD * p' > PROD * SUM
 *
 *          then SUM < 1
 *
 *      - therefore the function monotonically increase.
 *
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;
int n;
double p[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", p+i);
        p[i] *= 1e-6;
    }
    int l = 0, r = 0;
    double ans = 0, sum = 0, prod = 1;
    while (l < n) {
        while (r < n && sum < 1) {
            sum += p[r] / (1 - p[r]);
            prod *= (1 - p[r]);
            r += 1;
        }
        ans = max(ans, sum * prod);
        sum -= p[l] / (1 - p[l]);
        prod /= (1 - p[l]);
        l += 1;
    }
    printf("%d\n", (int)(1e6 * ans));
    return 0;
}