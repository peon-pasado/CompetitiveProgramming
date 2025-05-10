#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
char s[maxn];
int res[maxn];
unsigned h[maxn];
unsigned B = 1000 + rand() % 500;
unsigned powB[maxn];

int main() {
    powB[0] = 1;
    for (int i = 1; i < maxn; ++i) powB[i]=powB[i-1]*B;
    int t;
    scanf("%d", &t);
    for (int tc=1; tc<=t; ++tc) {
        scanf("%s", s);
        int n = strlen(s);
        memset(res, 0, sizeof res);
        res[1] = n;
        for (int k = 1; k <= n; ++k) {
            h[0] = 0;
            for (int i = 0; i < k; ++i) h[0]=h[0]*B+s[i];
            for (int i = 1; i + k <= n; ++i) h[i]=(h[i-1]-powB[k-1]*s[i-1])*B+s[i+k-1];
            for (int i = 0; i+k < n; ++i) {
                for (int j = i+k; j+k <= n; j += k) {
                    if (h[j] == h[j-k]) {
                        int len = j + k - i;
                        res[len / k] = max(res[len / k], len);
                    } else {
                        break;
                    }
                }
            }
        }
        printf("Case #%d:", tc);
        for (int i = 1; i <= n; ++i) printf(" %d", res[i]);
        puts("");
    }
    return 0;
}