#include <bits/stdc++.h>
using namespace std;


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    string t;
    cin>>t;
    vector<int> l, r;
    for (int i=0; i<n; ++i) {
        string s;
        cin>>s;
        int it = 0;
        for (auto c : s) {
            if (it < (int)t.size() && t[it] == c) it++;
        }
        l.push_back(it);
        reverse(s.begin(), s.end());
        int m = (int)t.size() - 1;
        it = 0;
        for (auto c : s) {
            if (it < (int)t.size() && t[m - it] == c) it++;
        }
        r.push_back(it);
    }
    sort(l.begin(), l.end());
    sort(r.rbegin(), r.rend());
    long long ans = 0;    
    for (int i=0, j = 0; i<n; ++i) {
        //cout << l[i] << ' ' << r[i] << endl;
        while (j < (int)r.size() && r[j] + l[i] >= (int)t.size()) ++j;
        ans += j;
    }
    cout << ans << '\n';
    return 0;
}