#include <bits/stdc++.h>
using namespace std;

const int maxn = 500;
bool found;
int n;
bool A[maxn][maxn];
int p[maxn];
bool vis[maxn];
void bt(int v, int len) {
    p[len] = v;
    if (found) return;
    if (len == n-1) {
        found = 1;
        for (int i=0; i<n; ++i) {
            printf("%d ", p[i]);
        }
        printf("%d\n", p[0]);
        return;
    }
    vis[v] = 1;
    for (int i=1; i<=n; ++i) {
        if (A[v][i] && !vis[i]) {
            bt(i, len+1);
        }
    }
    vis[v] = 0;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        int u, v;
        memset(A, 0, sizeof A);
        while (scanf("%d%d", &u, &v) == 2) {
            A[u][v] = A[v][u] = 1;
        }
        getchar();
        found = 0;
        bt(1, 0);
        if (!found) puts("N");
    }
    return 0;
}