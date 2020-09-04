/**
 * @author Miguel Mini
 * @tag dijsktra, spfa
 * @idea
 *      - we can solve reverse problem:
 * 
 *          "given k sources, what is the minimum
 *          time to reach 0 node"
 * 
 *      - To achieve that, each node can be used 
 *      only if it has already found its second best distance.
 * @complexity O(mlogn + n)
**/ 

#include <bits/stdc++.h>
#include "crocodile.h"
using namespace std;

const int maxn = 1e5 + 10;
int d[maxn];
int need[maxn];
using ii = pair<int, int>;
vector<int> g[maxn];

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
    for (int i = 0; i < M; ++i) {
        int u = R[i][0], v = R[i][1];
        g[u].emplace_back(i);
        g[v].emplace_back(i);
    }
    for (int i = 0; i < N; ++i) {
        need[i]= 2;
    }
    priority_queue<ii, vector<ii>, greater<ii>> q;
    for (int i = 0; i < K; ++i) {
        q.emplace(0, P[i]);
        need[P[i]] = 1;
    }
    int ans = -1;
    while (!q.empty()) {
        auto e = q.top(); q.pop();
        need[e.second] -= 1;
        if (need[e.second] != 0) continue;
        if (e.second == 0) ans = e.first;
        for (int ie : g[e.second]) {
            int temp = e.first + L[ie];
            int v = e.second ^ R[ie][0] ^ R[ie][1];
            if (need[v] <= 0) continue;
            q.emplace(temp, v);
        }
    }
    return ans;
}

/**
int n, m, k;
int R[maxn][2];
int L[maxn];
int P[maxn];

int main() {
    
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) cin >> R[i][0] >> R[i][1];
    for (int i = 0; i < m; ++i) cin >> L[i];
    for (int i = 0; i < k; ++i) cin >> P[i];
    cout << travel_plan(n, m, R, L, k, P) << endl;
    return 0;
}
**/
