#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    string s;
    cin>>s;
    sort(s.begin(), s.end());
    int ans = 0;
    for (long long i = 0; i * i < 1000'000'000'000'0LL; ++i) {
        long long t = i * i;
        string r = "";
        for (int j=0; j<n; ++j) {
            r.push_back(t % 10 + '0');
            t /= 10;
        }
        if (t > 0) break;
        sort(r.begin(), r.end());
        if (s == r) ans += 1;
    }
    cout << ans << '\n';
    return 0;
}