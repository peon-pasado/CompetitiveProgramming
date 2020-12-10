/**
 *  @author Miguel Mini
 *  @tag dfs, dp, dp_reroot, cycle_detection
 *  @idea
 *      - solve next node with dp rerooting
 *    
 *      - use cycle detection to reduce k.
 *
 *  @complexity O(n)
**/


#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
vector<int> g[maxn];
pair<int, int> tr[maxn][2];
int nxt[maxn];
int a[maxn];

void add(int x, pair<int, int> q) {
    q.first -= 1;
    if (q >= tr[x][0]) {
        tr[x][1] = tr[x][0];
        tr[x][0] = q;
    } else {
        tr[x][1] = max(tr[x][1], q);
    }
}

const int inf = 2e9;
void dfs(int x, int p) {
    tr[x][0] = {a[x], -x};
    tr[x][1] = {-inf, -inf};
    for (int v : g[x]) {
        if (v == p) continue;
        dfs(v, x);
        add(x, tr[v][0]);
    }
}

void dfs_push(int x, int p) {
    if (p) {
        auto temp = tr[p][0];
        temp.first += 1;
        auto res = tr[p][0];
        if (temp == tr[x][0]) {
            res = tr[p][1];
        }
        add(x, res);
    }
    for (int v : g[x]) {
        if (v == p) continue;
        dfs_push(v, x);
    }
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 0);
    dfs_push(1, 0);
    for (int i = 1; i <= n; ++i) {
        nxt[i] = -tr[i][tr[i][0].second == -i].second;
    }
    int tortoise = nxt[1];
    int hare = nxt[nxt[1]];
    while (tortoise != hare) {
        tortoise = nxt[tortoise];
        hare = nxt[nxt[hare]];
    }
    int mu = 0;
    tortoise = 1;
    while (tortoise != hare) {
        tortoise = nxt[tortoise];
        hare = nxt[hare];
        mu += 1;
    }
    int lam = 1;
    hare = nxt[tortoise];
    while (tortoise != hare) {
        hare = nxt[hare];
        lam += 1;
    }
    if (k > mu) k = (k - mu) % lam + mu;
    int x = 1;
    for (int i = 0; i < k; ++i) x = nxt[x];
    cout << x << endl;
    return 0;
}
