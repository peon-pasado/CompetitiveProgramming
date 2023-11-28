/**
 * @idea:
 *  - exhaustive backtracking.
**/

#include <bits/stdc++.h>
using namespace std;

int n;
int ring[16];
bool comp[40];
void dfs(int mask, int pos, int last) {
    if (pos == n) {
        if (!comp[last + 1]) {
            for (int i=0; i<n; ++i) {
                cout << ring[i] << " \n"[i+1==n];
            }
        }
        return;
    }
    for (int i=1; i<=(pos==0?1:n); ++i) {
        if ((~mask & (1<<i)) && !comp[last + i]) {
            ring[pos] = i;
            dfs(mask | (1<<i), pos+1, i);
        }
    }

}

int main() {
    for (int i=2; i<=31; ++i) {
        for (int j=2; j*j<=i; ++j) {
            if (i % j == 0) {
                comp[i] = 1;
                break;
            }
        }
    }
    int tc=1;
    while (cin>>n) {
        if (tc>1) cout << '\n';
        cout << "Case " << tc++ << ":" << '\n';
        dfs(0, 0, 0);
    }
    return 0;
}