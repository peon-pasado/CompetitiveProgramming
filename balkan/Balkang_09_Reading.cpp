/**
 *  @author Miguel Mini
 *  @tag matrix_exponentiation, automaton
 *  @idea
 *      - create the automaton with weights 1
 *    
 *      - put a sink node
 *
 *      - create a loop in the sink node
 *
 *      - calcule A^{n+1} with A the automaton matrix
 *
 *      - note that we just need maxF * sigma nodes.
**/

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 300;
int g[maxn][maxn], A[maxn][maxn], B[maxn][maxn];
bool vis[maxn][maxn];
int nodes[maxn][6];
int S = 25;

void add_edge(int u, int v, int f) {
    if (~nodes[u][f]) {
        g[nodes[u][f]][v] = 1;
        return;
    }
    int& t = nodes[u][f];
    while (f > 1) {
        g[u][++S] = 1;
        u = S;
        f -= 1;
    }
    g[t=u][v] = 1;
}


int main() {
    memset(nodes, -1, sizeof nodes);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        char a, b;
        int c;
        cin >> a >> b >> c;
        a -= 'a'; b -= 'a';
        vis[a][b] = 1;
        vis[b][a] = 1;
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = i; j < 26; ++j) {
            if (!vis[i][j]) {
                g[i][j] = 1;
                g[j][i] = 1;
            }    
        }
    }
    ++S;
    for (int i = 0; i < 26; ++i) {
        g[i][S] = 1;
    }
    g[S][S] = 1;
    ++S;
    auto mul = [&](int R[maxn][maxn], int X[maxn][maxn], int Y[maxn][maxn]) {
        memset(B, 0, sizeof B);
        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < S; ++j) {
                for (int k = 0; k < S; ++k) {
                    B[i][j] = (B[i][j] + X[i][k]*1ll*Y[k][j]%mod)%mod;
                }
            }
        }
        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < S; ++j) {
                R[i][j] = B[i][j];
            }
        }
    };
    for (int i = 0; i < S; ++i) A[i][i] = 1;
    n += 1;
    while (n > 0) {
        if (n&1) mul(A, A, g);
        mul(g, g, g);
        n >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < 26; ++i) {
        ans = (ans + A[i][S-1]) % mod;
    }
    cout << ans << endl;
    return 0;
}
