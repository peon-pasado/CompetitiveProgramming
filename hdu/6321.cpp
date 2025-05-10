#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define __builtin_popcount __popcnt
using namespace std;

const int maxn = 10;
const int mod = 1e9 + 7;
int dp[1<<maxn];
int C[maxn][maxn];
vector<int> pi[maxn][maxn];
int n;

int add(int a, int b) {
    return a+b>=mod?a+b-mod:a+b;
}

int ans[10];

void update(int x, int y, int d) { //2^{n-2} 
    int trs = (1<<x) ^ (1<<y);
    for (int i = 0; i < pi[x][y].size(); ++i) {
        int s = pi[x][y][i];
        int k = __builtin_popcount(s) / 2;
        int temp = dp[s ^ trs];
        if (d == -1) temp = mod - temp;
        dp[s] = add(dp[s], temp); 
        ans[k] = add(ans[k], temp);
    }
    C[x][y] += d;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        int m;
        cin>>n>>m;
        
        for (int i=1; i<1<<n; ++i) {
            int k = __builtin_popcount(i);
            if (k % 2 == 0) {
                for (int x=0; x<n; ++x) if (i & (1<<x))
                    for (int y=x+1; y<n; ++y) if (i & (1<<y)) {
                        pi[x][y].push_back(i);
                    }
            }
        }

        dp[0] = 1;
        while (m--) {
            string type;
            cin>>type;
            int u, v;
            cin>>u>>v; 
            u--; v--;
            update(u, v, type == "-" ? -1 : 1);
            for (int k = 1; 2 * k <= n; ++k) {
                cout << ans[k] << " \n"[2*k==n];
            }
        }
        
        for (int i=0; i<n; ++i)
            for (int j=i+1; j<n; ++j)
                pi[i][j].clear();
        memset(ans, 0, sizeof ans);
        memset(C, 0, sizeof C);
        memset(dp, 0, sizeof dp);
    }
    return 0;
}