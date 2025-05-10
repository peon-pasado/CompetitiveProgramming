#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
const int mod = 1e8 + 7;
const int p = 257;
int n, q;
char s[MAXN];
int ft[2][MAXN];
int P[MAXN], iP[MAXN];

int add(int a, int b) {
    return (a+b)%mod;
}
int mul(long long a, long long b) {
    return a*b%mod;
}
int ex(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

void update(int id, int pos, int v) {
    while (pos < MAXN) {
        ft[id][pos] = add(ft[id][pos], v);
        pos += pos&-pos;
    }
}
int query(int id, int pos) {
    int ans = 0;
    while (pos > 0) {
        ans = add(ans, ft[id][pos]);
        pos -= pos&-pos;
    }
    return ans;
}

int main() {
    scanf("%s", s);
    scanf("%d\n", &q);
    n = strlen(s);
    P[0] = 1;
    for (int i = 1; i < n; ++i) P[i] = mul(P[i-1], p);
    iP[0] = 1; 
    int invp = ex(p, mod-2);
    for (int i = 1; i < n; ++i) iP[i] = mul(iP[i-1], invp);
    
    for (int i = 0; i < n; ++i) {
        update(0, i+1, mul(s[i], P[i]));
        update(1, i+1, mul(s[i], P[n-1-i]));
    }
    
    while (q--) {
        char type[20];
        scanf("%s", type);
        if (type[0] == 'c') {
            int pos;
            char c;
            scanf("%d %c\n", &pos, &c);
            int last0 = query(0, pos) - query(0, pos-1);
            int last1 = query(1, pos) - query(1, pos-1);
            update(0, pos, mul(c, P[pos-1]) + mod - last0);
            update(1, pos, mul(c, P[n-pos]) + mod - last1);
        } else {
            int l, r;
            scanf("%d %d\n", &l, &r);
            int q0 = mul(query(0, r) + mod - query(0, l-1), iP[l-1]);
            int q1 = mul(query(1, r) + mod - query(1, l-1), iP[n-r]);
  
          
            cout << (q0 == q1 ? "Yes" : "No") << endl;
        }
    }
    
    return 0;
}