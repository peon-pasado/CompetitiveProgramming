/**
 * @idea backtracking
 * 
 *  - sorting by neighbor and simule with backtracking every 
 * Hamiltonian cycle.
 * 
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int g[21][3];
int c;
vector<int> r;
int mx;
int s;
void dfs(int mask, int v) {
    if (mask == 0) {
        if (mx & (1<<v)) {
            cout << ++c << ": ";
            r.push_back(s);
            for (int i=0; i<=20; ++i) {
                cout << ' ' << r[i];
            }
            r.pop_back();
            cout << '\n';
        }
        return;
    }
    for (int i=0; i<3; ++i) {
        if (mask & (1<<g[v][i])) {
            r.push_back(g[v][i]);
            dfs(mask ^ (1<<g[v][i]), g[v][i]);
            r.pop_back();
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i=1; i<=20; ++i) {
        for (int j=0; j<3; ++j) {
            cin>>g[i][j];
        }
        sort(g[i], g[i]+3);
    }
    int src;
    while (cin>>src, src) {
        mx = 0; c = 0; s=src;
        for (int i=0; i<3; ++i) mx |= 1<<g[src][i];
        r.push_back(src);
        dfs((((1<<20) - 1) << 1) ^ (1<<src), src);
        r.pop_back();
    }
    return 0;
}
