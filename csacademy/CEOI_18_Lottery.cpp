/**
 * @author Miguel Mini
 * @tag sorting, accumulate, coordinate_compression
 * @idea
 *      - use coordinate compression over k_i
 *
 *      - compute arr[j] = t[i + j] != t[j] for all i, j
 *
 *      - add contribution of arr[j + l - 1] - arr[j-1]
 *      to j and i+j position.
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 2;
int pos[105], inv[maxn];
int acc[maxn];
int f[maxn][105];
int n, l;
int a[maxn];
int q, k;

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a+i);
    }
    scanf("%d", &q);
    set<int> m;
    m.insert(l);
    for (int i = 0; i < q; ++i) {
        scanf("%d", pos+i);
        m.insert(pos[i]);
    }
    int ti = 0;
    memset(inv, 1, sizeof inv);
    for (auto& e : m) {
        inv[e] = ti++;
    }
    for (int i = l-1; i >= 0; --i) {
        inv[i] = min(inv[i], inv[i+1]);
    }
    for (int i = 0; i < n - l + 1; ++i) {
        acc[1] = a[i] != a[0];
        for (int j = 1; j + i < n; ++j) {
            acc[j+1] = acc[j] + (a[i+j] != a[j]);
        }
        for (int j = 0; i + j < n - l + 1; ++j) {
            int dt = inv[acc[j + l] - acc[j]];
            f[j][dt] += 1;
            f[j+i][dt] += 1;
        }
    }
    for (int i = 0; i < n - l + 1; ++i) {
        for (int j = 1; j < q; ++j) {
            f[i][j] += f[i][j-1];
        }
    }
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < n - l + 1; ++j) {
            printf("%d ", f[j][inv[pos[i]]] - 2);
        }
        puts("");
    }
    return 0;
}