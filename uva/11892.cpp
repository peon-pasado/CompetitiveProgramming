#include <bits/stdc++.h>
using namespace std;

const int maxn = 20010;
int a[maxn];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int r = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", a+i);
            r += a[i] == 1;
        }
        puts((r < n || r % 2) ? "poopi" : "piloop");
    }
    return 0;
}