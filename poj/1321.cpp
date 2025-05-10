#include <cstdio>
using namespace std;

char T[10][10];
int n, k;
int cnt(int pos, int mask, int m) {
    if (pos == n) return m == k;
    int ans = cnt(pos+1, mask, m);
    for (int i=0; i<n; ++i) {
        if (T[pos][i] == '#' && (~mask&(1<<i))) {
            ans += cnt(pos+1, mask | (1<<i), m+1);
        }   
    }
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &k), n>0) {
        for (int i=0; i<n; ++i) scanf("%s", T[i]);
        printf("%d\n", cnt(0, 0, 0));
    }
    return 0;
}