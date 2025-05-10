#include <bits/stdc++.h>
using namespace std;

const int maxn = 4102;
bitset<maxn * 4> a[maxn];
int id[300];
int d[maxn][4];
int n, m, k;
int calc[maxn][maxn];
int cc[maxn][4];
string s[maxn];

bool check(int i) {
    for (int j=0; j<m; ++j)
        cc[j][id[s[i][j]]]--;
    int acc = 0;
    for (int j=0; j<m; ++j) {
        acc += cc[j][id[s[i][j]]];
    }
    for (int j=0; j<m; ++j)
        cc[j][id[s[i][j]]]++;
    return acc == (m - k) * (n - 1);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    id['A'] = 0;
    id['C'] = 1;
    id['G'] = 2;
    id['T'] = 3;
    cin>>n>>m>>k;
    for (int i=0; i<n; ++i) {
        cin>>s[i];
        for (int j=0; j<m; ++j) {
            a[i][4*j + id[s[i][j]]] = 1;
            cc[j][id[s[i][j]]]++;
        }
    }
    memset(calc, -1, sizeof calc);
    vector<bool> bad(n);
    for (int i=0; i<n; ++i) {
        if (bad[i]) continue;
        if (!check(i)) continue;
        int cnt = 0;
        for (int j=0; j<n; ++j) if (i != j) {
            if (calc[i][j] == -1) {
                calc[i][j] = calc[j][i] = (a[i] ^ a[j]).count();
            } 
            int diff = calc[i][j];
            if (diff == 2*k) {
                cnt++;
            } else {
                bad[j] = 1;
                break;
            }
        }
        if (cnt == n-1) {
            cout << i + 1 << '\n';
            exit(0);
        }
    }
    return 0;
}