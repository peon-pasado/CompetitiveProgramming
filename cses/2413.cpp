#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 1e6 + 2;
long long f[maxn][5];

int main() {
    f[0][0] = 1; 
    for (int i=1; i<maxn; ++i) {
        f[i][0] += 2 * f[i-1][0]; 
        f[i][0] += f[i-1][1];
        f[i][0] += f[i-1][2];
        f[i][0] += f[i-1][3];
        f[i][0] += f[i-1][4];

        f[i][1] += f[i-1][0];
        f[i][1] += f[i-1][1];
        
        f[i][2] += f[i-1][0];
        f[i][2] += f[i-1][2];
        f[i][2] += f[i-1][3];
        f[i][2] += f[i-1][4];

        f[i][3] += f[i-1][0];
        f[i][3] += f[i-1][2];
        f[i][3] += f[i-1][3];
        f[i][3] += f[i-1][4];

        f[i][4] += f[i-1][0];
        f[i][4] += f[i-1][2];
        f[i][4] += f[i-1][3];
        f[i][4] += f[i-1][4];

        for (int j=0; j<5; ++j) 
            f[i][j] %= mod;
    }
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        cout << f[n][0] << '\n';
    }
    return 0;
}