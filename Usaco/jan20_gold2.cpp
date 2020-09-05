/**
 * @author Miguel Mini
 * @tag sweep_line, BIT
 * @idea
 *     - we can solve in offline approach.
 *  
 *     - fix a endpoint i, we can solve in O(i) 
 *      the number  of unordered triplets j < k < i
 *      such that a_j + a_k + a_i = 0. 
 *  
 *     - then update to all the intervals that 
 *      have not come out that start in a position 
 *      greater than or equal to j.
**/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
const int maxq = 1e5 + 10;
const int maxa = 1e6 + 10;
int a[maxn];
queue<int> qu[maxn];
using ll = long long;
ll res[maxq];
int L[maxq];
ll ft[maxn];
int cnt[2 * maxa];

void upd(int x, int v) {
    while (x<maxn) {
        ft[x] += v;
        x += x&-x;
    }
}

ll qry(int x) {
    ll ans=0;
    while (x>0) {
        ans += ft[x];
        x -= x&-x;
    }
    return ans;
}

int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i=1; i<=n; ++i) {
        scanf("%d", a+i);
    }
    for (int i=0; i<q; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        qu[r].push(i);
        L[i] = l;
    }
    for (int i=1; i<=n; ++i) {
        for (int j=i-1; j>=1; --j) {
            if (abs(a[j] + a[i]) < maxa) {
                int v = cnt[maxa-(a[j] + a[i])];
                upd(1, v);
                upd(j+1, -v);
            }
            cnt[maxa+a[j]]+=1;
        }
        for (int j=1; j<i; ++j) cnt[maxa+a[j]] = 0;
        while (!qu[i].empty()) {
            auto q = qu[i].front(); qu[i].pop();
            res[q] = qry(L[q]);
        }
    }
    for (int i=0; i<q; ++i) {
        printf("%lld\n", res[i]);
    }
    return 0;
}
