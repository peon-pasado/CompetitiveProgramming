#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> p;
int t[10];
void up(int t[], int x) {
    t[2] = x;
    sort(t, t+3);
    reverse(t, t+3);
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n;
        cin>>n;
        p.clear();
        for (int i = 0; i < n; ++i) {
            int s, d;
            cin>>s>>d;
            p.push_back({d, s});
        }
        sort(p.begin(), p.end());
        int f[10] = {0};
        int tim=0;
        for (int i = 0; i < n; ++i) {
            up(f, max(0, - p[i].first + p[i].second + tim));
            tim += p[i].second;
        }
        int ans = f[0] + f[1];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= n; ++j) {
                int u[10] = {0};
                int tim=0;
                for (int k = 0; k < j; ++k) 
                    if (i != k) {
                        up(u, max(0, - p[k].first + p[k].second + tim));
                        tim += p[k].second;
                    }
                up(u, max(0, - p[i].first + p[i].second + tim));
                tim += p[i].second;
                for (int k = j; k < n; ++k)
                    if (i != k) {
                        up(u, max(0, -p[k].first + p[k].second + tim));
                        tim += p[k].second;
                    }
                ans = min(ans, u[0] + u[1]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}