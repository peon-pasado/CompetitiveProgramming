/**
 * @author Miguel Mini
 * @tag hashing, number_theory
 * @idea
 *      - we can find the answer
 *      for every period k.
 *  
 *      - we can start in all
 *      position i, and see that
 *      the first m blocks of size
 *      k are equals in O(n^2 / k).
 *
 * @complexity O(n^2 logk) 
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
char s[maxn];
int res[maxn];
unsigned h[maxn];
unsigned B = 1000 + rand() % 500;
unsigned powB[maxn];

int main() {
    powB[0]=1;
    for (int i = 1; i<maxn; ++i) powB[i]=powB[i-1]*B;
    int t;
    scanf("%d", &t);
    for (int tc=1; tc<=t; ++tc) {
        scanf("%s", s);
        int n=strlen(s);
        res[1]=n;
        for (int i=2; i<=n; ++i) res[i]=0;
        for (int k = 1; k <= n; ++k) {
            h[0]=0;
            for (int i=0; i<k; ++i)
                h[0]=h[0]*B+s[i];
            for (int i=1; i<=n-k; ++i)
                h[i]=(h[i-1]-powB[k-1]*s[i-1])*B+s[i+k-1];
            for (int i=0; i<n-k; ++i) {
                for (int j = 1; i+(j+1)*k <= n; ++j) {
                    if (h[i+j*k] == h[i+(j-1)*k])
                        res[j+1]=max(res[j+1], (j+1)*k);
                    else break;
                }
            }
        }
        printf("Case #%d:", tc);
        for (int i=1; i<=n; ++i) printf(" %d", res[i]);
        puts("");
    }
    return 0;
}