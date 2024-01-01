/**
 * @idea backtracking, math
 * 
 * - we can count the number of sequences of 
 * digits 0-9 with #digits of r.
 * 
 * - the number of sequences is \binom{18 + 9}{9} 
 * 
 * - we can check in O(\log^2{r}) or O(\log(r))
 * if a configuration is between l and r.
 * 
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> sl, sr;
int n;
int v[21];

vector<int> get_string(long long x) {
    vector<int> res;
    while (x > 0) {
        res.push_back(x % 10);
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int cnt[10];
bool verify(int v[]) {
    memset(cnt, 0, sizeof cnt);
    for (int i=0; i<n; ++i) {
        cnt[v[i]]++;
    }
    int len = 0;
    while (len < n && sl[len] == sr[len]) {
        if (cnt[sl[len]] == 0) return 0;
        --cnt[sl[len++]];
    }
    if (len == n) return 1;
    for (int i=sl[len]+1; i<sr[len]; ++i) {
        if (cnt[i] > 0) return 1;
    }
    int c2[10];
    for (int i=0; i<10; ++i) c2[i] = cnt[i];
    for (int j=len; j<n; ++j) {
        if (c2[sl[j]] == 0) break;
        c2[sl[j]]--;
        if (j + 1 == n) return 1;
        for (int k = sl[j+1] + 1; k <= 9; ++k) {
            if (c2[k] > 0) return 1;
        }
    }
    for (int i=0; i<10; ++i) c2[i] = cnt[i];
    for (int j=len; j<n; ++j) {
        if (c2[sr[j]] == 0) break;
        c2[sr[j]]--;        
        if (j + 1 == n) return 1;
        for (int k = 0; k < sr[j+1]; ++k) {
            if (c2[k] > 0) return 1;
        }
    }
    return 0;
}

int bt(int pos, int last) {
    if (pos == n) return verify(v);
    int ans = 0;
    for (int d = last; d <= 9; ++d) {
        v[pos] = d;
        ans += bt(pos+1, d);
    }
    return ans;
}

int main() {
    long long l, r;
    cin>>l>>r;
    sl = get_string(l);
    sr = get_string(r); 
    n = sr.size();
    reverse(sl.begin(), sl.end());
    while (sr.size() > sl.size()) sl.push_back(0);
    reverse(sl.begin(), sl.end());
    cout << bt(0, 0) << '\n';
    return 0;
}