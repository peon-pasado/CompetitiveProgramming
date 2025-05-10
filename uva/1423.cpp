#include <bits/stdc++.h>
using namespace std;

const int maxn = 12;
char s[maxn][maxn];
int sum[maxn][maxn];
int n;

bool can(int p, int x) {
    for (int j = 0; j < p; ++j) {
        int temp = sum[j][p-1] + x;
        if (s[j][p] == '0' && temp != 0) return 0;
        if (s[j][p] == '+' && temp <= 0) return 0;
        if (s[j][p] == '-' && temp >= 0) return 0; 
    }
    return 1;
}

bool sol = false;
void bt(int pos) {
    if (sol) return;
    if (pos == n) {
        sol = true;
        for (int i = 0; i < n; ++i) {
            cout << sum[i][i] << " \n"[i+1==n];
        }
        return;
    }
    int l = 0, r = 0;
    if (s[pos][pos] == '+') l = 1, r = 10;
    if (s[pos][pos] == '-') l = -10, r = -1;
    for (int i = l; i <= r; ++i) {
        if (can(pos, i)) {
            for (int j = 0; j <= pos; ++j) {
                sum[j][pos] = sum[j][pos-1] + i;
            }
            bt(pos+1);
        }
    }
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        cin>>n;
        cin.get();
        memset(s, '_', sizeof s);
        for (int i=0; i<n; ++i) {
            for (int j=i; j<n; ++j) {
                s[i][j] = cin.get();
            }
            s[i][n] = '\0';
        }
        sol = false;
        bt(0);
    }
    return 0;
}