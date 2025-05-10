#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
const int maxn = 1e5+10;
const int maxm = 18;
int F[1<<maxm][2];
int a[maxn];
int rnk[maxn], lnk[maxn];
int n, M;

void init(int x) {
    lnk[x]=x; rnk[x]=0;
}

int get(int x) {
    return x==lnk[x]?x:lnk[x]=get(lnk[x]);
}

bool merge(int x, int y) {
    x=get(x); y=get(y);
    if (x==y) return 0;   
    if (rnk[x]<rnk[y]) swap(x, y);
    rnk[x] += rnk[x]==rnk[y];
    lnk[y] = x;
    return 1;
}

void add(int x, int c) {
    if (c == 0) return;
    if (F[x][0]==0) F[x][0]=c;
    else if (F[x][0]>c) F[x][1]=F[x][0], F[x][0]=c;
    else if (F[x][0]<c) {
        if (F[x][1] == 0) F[x][1] = c;
        else F[x][1]=min(F[x][1], c);
    }
}

void update(int x, int y) {
    add(x, F[y][0]);
    add(x, F[y][1]);
} 

void make() {
    for (int s=0; s<1<<M; ++s) F[s][0]=F[s][1]=0;
    for (int i = 1; i <= n; ++i)
        add(a[i], get(i));
    for (int k=0; k<M; ++k)
        for (int s=0; s<1<<M; ++s)
            if ((~s)&(1<<k))
                update(s, s^(1<<k));
}

int max_id[maxn], max_val[maxn];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>M;
    for (int i=1; i<=n; ++i) cin>>a[i];
    for (int i=1; i<=n; ++i) init(i);
    int m = 0;
    long long ans = 0;
    while (m < n-1) {
        make();
        for (int i=1; i<=n; ++i) max_id[i] = 0;
        for (int i=1; i<=n; ++i) {
            int c = get(i);
            int x = 0;
            for (int k=M-1; k>=0; --k) {
                if (a[i] & (1<<k)) {
                    int mk = x ^ (1<<k);
                    if (F[mk][0]==0) continue;
                    if (F[mk][0] != c || (F[mk][1] != c && F[mk][1] != 0)) {
                        x = mk;
                    } 
                }
            }
            int d = F[x][F[x][0]==c];        
            if (max_id[c] == 0 || max_val[c] < (x&a[i])) { 
                max_id[c] = d;
                max_val[c] = x & a[i];
            }
        }
        for (int i=1; i<=n; ++i) {
            if (lnk[i]==i) {
                if (merge(i, max_id[i])) {
                    m++;
                    ans += max_val[i];
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}