#include <bits/stdc++.h>
#define int64_t long long
using namespace std;

const int maxn = 2e6 + 10;
int64_t a[maxn];
int t[maxn * 2];
int n, q, op;

int m;
void build() {
    m = n+1;
    for (int i=0; i<m; ++i) t[m + i] = i;
    for (int i=m-1; i>0; --i) t[i] = a[t[i<<1]] > a[t[i<<1|1]] ? t[i<<1] : t[i<<1|1];
}

int query(int l, int r) {  
  if (r < l) return 0;
  r += 1;
  int res = 0;
  for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
    if (l&1) {
        res = a[res] > a[t[l]] ? res : t[l];
        l++;
    }
    if (r&1) {
        r--;
        res = a[res] > a[t[r]] ? res : t[r];
    }
  }
  return res;
}


int64_t eval(int i, int j) {
    if (j == 0) return 0;
    return a[j] + a[i] % a[j];
}

vector<pair<int, int>> fl[maxn], fr[maxn]; 
int stk[maxn], bck[maxn];
int top;
int sz;
int cc[maxn];
void init() {
    int res = 0;
    for (int i=1; i<=n; ++i) {
        fl[i].emplace_back(i, 0);
        int cnt = 0;
        int mx = 0;
        int id = 0;
        sz = 0;
        while (top > 0) {
            int j = stk[top--];
            bck[sz++] = j;
            if (a[j] > a[mx]) {
                if (eval(i, id) < eval(i, mx)) id = mx;
                mx = j;
            } else {
                if (eval(i, id) < eval(i, j)) id = j;
            }
            fl[i].emplace_back(j, id);
            if (a[j] > a[i] / 2) {
                if (++cnt == 2) break;
            } else {
                cc[j]++;
            }
        }
        reverse(fl[i].begin(), fl[i].end());
        for (int j=sz-1; j>=0; --j) if (cc[bck[j]] <= 1) stk[++top] = bck[j];   
        stk[++top] = i;
    }
    for (int i=1; i<=n; ++i) cc[i] = 0;
    top = 0;
    for (int i=n; i>=1; --i) {
        fr[i].emplace_back(i, 0);
        int cnt = 0; 
        int mx = 0;
        int id = 0;
        sz = 0;
        while (top > 0) {
            int j = stk[top--];
            bck[sz++] = j;
            if (a[j] > a[mx]) {
                if (eval(i, id) < eval(i, mx)) id = mx;
                mx = j;
            } else {
                if (eval(i, id) < eval(i, j)) id = j;
            }
            fr[i].emplace_back(j, id);
            if (a[j] > a[i] / 2) {
                if (++cnt == 2) break;
            } else {
                cc[j]++;
            }
        }
        for (int j=sz-1; j>=0; --j) if (cc[bck[j]] <= 1) stk[++top] = bck[j];  
        stk[++top] = i;
    }
    
} 

const int64_t inf = 5e18;
int64_t query_mod(int x, int l, int r) {
    //assert(lower_bound(fl[x].begin(), fl[x].end(), make_pair(l, (int64_t)-1)) != fl[x].end());
    int i = lower_bound(fl[x].begin(), fl[x].end(), make_pair(l, -1))->second;
    //assert(upper_bound(fr[x].begin(), fr[x].end(), make_pair(r, inf)) != fr[x].begin());
    int j = (--upper_bound(fr[x].begin(), fr[x].end(), make_pair(r, n+1)))->second;
    return max(eval(x, i), eval(x, j));
}

int64_t solve(int l, int r) {
    int x = query(l, r);
    int y = query(l, x-1), z = query(x+1, r);
    if (a[y] < a[z]) {
        swap(y, z);
    }
    int64_t res = eval(x, z) + a[y];
    if (x < y) res = max(res, eval(y, query(y+1, r)) + a[x] % a[y]);
    else res = max(res, eval(y, query(l, y-1)) + a[x] % a[y]);
    res = max(res, query_mod(x, l, r) + a[y]);
    res = max(res, query_mod(y, l, r) + a[x] % a[y]);
    return res;
}

int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0') c = getchar();
    while (c >= '0') {
        x = (x<<3) + (x<<1) + c - '0';
        c = getchar();
    }
    return x;
}

int64_t read_ll() {
    int64_t x = 0;
    char c = getchar();
    while (c < '0') c = getchar();
    while (c >= '0') {
        x = (x<<3) + (x<<1) + c - '0';
        c = getchar();
    }
    return x;
}

char ch[22];
void print(int64_t x) {
    int t = 0;
    while (x > 0) {
        ch[t++] = '0' + x % 10;
        x /= 10;
    }
    reverse(ch, ch+t); ch[t] = 0;
    puts(ch);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>q>>op;
    //n = read_int();
    //q = read_int();
    //op = read_int();
    for (int i=1; i<=n; ++i) {
        //a[i] = read_ll();
        cin>>a[i];
    }
    build();
    init();
    int64_t lans = 0;
    while (q--) {
        int l;// = read_int();
        int r;// = read_int();
        cin>>l>>r;
        if (op) {
            l = (l + lans - 1) % n + 1;
            r = (r + lans - 1) % n + 1;
        }
        cout << (lans = solve(l, r)) << '\n';
    }
    return 0;
}