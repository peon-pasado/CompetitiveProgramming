#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 50010;
const int maxc = 302;
int memo[2][maxc][2];
int n, a, b;

int add(int a, int b) {
    return (a+b)%mod;
}

int main() {
    cin >> n >> a >> b;
    for (int pos = n; pos >= 0; --pos) {
        for (int cnt = 0; cnt <= max(a, b); ++cnt) {
            for (int t = 0; t < 2; ++t) {
                int& ans = memo[pos&1][cnt][t] = 0;
                if (t == 0 and cnt > a) continue;   
                if (t == 1 and cnt > b) continue;
                if (pos == n) {
                    ans = 1;
                    continue;
                }
                for (int i = 0; i < 2; ++i) {
                    if (i == t) {
                        ans = add(ans, memo[(pos+1)&1][cnt+1][i]);
                    } else {
                        ans = add(ans, memo[(pos+1)&1][1][i]); 
                    }
                }
            }
        }
    }
    cout << memo[0][0][0] << endl;
    return 0;
}