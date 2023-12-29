/**
 * @idea backtracking, graphs
 * 
 * - simule all paths, mark nodes.
 * 
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
vector<int> adj[maxn];
int n, k;

int arr[maxn];
bool vis[maxn];
bool found;
void bt(int x, int len) {
    arr[len] = x;
    if (len == k) {
        found = 1;
        for (int i=0; i<=k; ++i) {
            cout << "(,"[i>0] << arr[i];
        }
        cout << ")\n";
        return;
    } 
    vis[x] = 1;
    for (int v : adj[x]) {
        if (vis[v]) continue;
        bt(v, len+1);
    }
    vis[x] = 0;
}

int main() {
    int t = 0;
    while (cin>>n>>k) {
        for (int i=1; i<=n; ++i) adj[i].clear();
        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=n; ++j) {
                int x;
                cin>>x;
                if (x) adj[i].push_back(j);
            }
        }
        if (t++ > 0) cout << '\n'; 
        found = 0;
        bt(1, 0);
        if (!found) cout << "no walk of length " << k << '\n';
        cin.ignore(6);
    }
    return 0;
}