/**
 * @author Miguel Mini
 * @tag dfs, greedy
 * @idea
 *    - the answer is (leaf + 1) / 2
 *
 *    - we need to find a way to join the sheets 
 *    in such a way that any subtree of a node is 
 *    connected to a different subtree. We greedily 
 *    gather each (leaf + 1) / 2 leaves.
 *
**/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 10;
vector<int> g[maxn];
int n;

void dfs(vector<int>& nodes, int x, int p=0) {
    if (g[x].size() == 1) nodes.emplace_back(x);
    for (int v : g[x]) {
        if (v==p) continue;
        dfs(nodes, v, x);
    }
}

int main() {
    scanf("%d", &n);
    for (int i=0; i<n-1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    vector<int> nodes;
    dfs(nodes, 1);
    cout << (nodes.size() + 1) / 2 << endl;
    for (int i = 0; i < nodes.size() / 2; ++i) {
        cout << nodes[i] << " " << nodes[(nodes.size() + 1) / 2 + i] << endl;
    }
    if (nodes.size() & 1) cout << 1 << " " << nodes[nodes.size() / 2] << endl;
    return 0;
}
