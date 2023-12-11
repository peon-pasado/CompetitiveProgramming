/**
 * @idea backtracking, iterative-deepening, prune
 * 
 *  - we can simule the process for select every character.
 * 
 *  - we can use iterative-deepening to get the minimum length.
 * 
 *  - we can prune with:
 * 
 *      - ceil(missing characters / n)
 * 
 *      - sum of maximum of every character in the sequences.
 * 
**/

#include <iostream>
#include <algorithm>
using namespace std;

string s[10];
int sum, n;
int l[10];
string r = "AGCT";
int invr[300];
int c[10][4];

bool bt(int pos, int len, int taked) {
    if (pos == len) return sum == taked;
    if (pos + (sum - taked + n - 1) / n > len) return 0;
    int extra = 0;
    for (int i=0; i<4; ++i) {
        int dd = 0;
        for (int j=0; j<n; ++j) dd = max(dd, c[j][i]);
        extra += dd;
    }
    if (pos + extra > len) return 0;
    int mask[5];
    pair<int, int> d[5];
    for (int i=0; i<4; ++i) {
        mask[i] = 0;
        d[i].second = i;
    }
    for (int i=0; i<n; ++i) {
        if (l[i] < (int)s[i].size()) 
            mask[invr[s[i][l[i]]]] |= 1<<i; 
    }
    for (int i=0; i<4; ++i) {
        d[i].first = __builtin_popcount(mask[i]);
    }
    sort(d, d+4);
    for (int i=3; i>=0; --i) {
        int t = d[i].second;
        for (int j=0; j<n; ++j) if (mask[t] & (1<<j)) l[j]++, c[j][t]--;
        if (d[i].first > 0 && bt(pos+1, len, taked + d[i].first)) return 1;
        for (int j=0; j<n; ++j) if (mask[t] & (1<<j)) l[j]--, c[j][t]++;
    }
    return 0;
}

int main() {
    for (int i=0; i<4; ++i) invr[r[i]] = i;
    int t;
    cin>>t;
    while (t--) {
        cin>>n;
        sum = 0;
        int mx = 0;
        for (int i=0; i<n; ++i) {
            cin>>s[i];
            l[i] = 0;
            sum += (int)s[i].size();
            mx = max(mx, (int)s[i].size());
            for (int j=0; j<4; ++j) c[i][j] = 0;
            for (int j=0; j<(int)s[i].size(); ++j)
                c[i][invr[s[i][j]]]++;
        }
        int len = max(mx, (sum + n - 1) / n);
        while (!bt(0, len, 0)) {
            for (int i=0; i<n; ++i) l[i] = 0;
            len++;
        }
        cout << len << '\n';
    }
    return 0;
}