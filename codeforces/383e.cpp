#include <bits/stdc++.h>
using namespace std;

int F[1<<24];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    for (int i=0; i<n; ++i) {
        string s;
        cin>>s;
        int mask = 0;
        for (auto c : s) {
            mask |= 1 << (c - 'a');
        }
        F[(1<<24) - 1 - mask]++;
    }    
    for (int i=0; i<24; ++i)
        for (int j=0; j<1<<24; ++j)
            if (~j & (1<<i))
                F[j] += F[j ^ (1<<i)]; 
    
    long long ans = 0;
    for (int i=1; i<1<<24; ++i) {
        ans ^= 1LL * (n - F[i]) * (n - F[i]);
    }
    cout << ans << '\n';
    return 0;
}