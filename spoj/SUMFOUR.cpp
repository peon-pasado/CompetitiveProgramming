#include <bits/stdc++.h>
using namespace std;

const int maxn = 2510;
int x[maxn][4];
int A[maxn * maxn], B[maxn * maxn];

int main() {
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> x[i][j];
        } 
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i * n + j] = x[i][0] + x[j][1];
            B[i * n + j] = -x[i][2] - x[j][3]; 
        }
    }
    sort(A, A+n*n);
    sort(B, B+n*n);
    long long ans = 0;
    for (int i = 0, j = 0; i < n*n && j < n * n;) {
        if (A[i] < B[j]) ++i;
        else if (B[j] < A[i]) ++j;
        else {
            int na = i, nb = j;
            while (i + 1 < n * n && A[i] == A[i+1]) ++i;
            while (j + 1 < n * n && B[j] == B[j+1]) ++j;
            ++i; ++j;
            ans += (i - na) *1ll* (j - nb);
        }
    }
    cout << ans << '\n';
    return 0;
}