#include <bits/stdc++.h>
using namespace std;

const int N = 20;
int w[N];
long long mid;
int n;

int bt(int pos, int sum) {
    if (pos == n) return sum == mid; 
    return bt(pos+1, sum) + bt(pos+1, sum+w[pos]);    
}

int main() {
    cin>>n;
    for (int i=0; i<n; ++i) {
        cin>>w[i];
        mid += w[i];
    }
    if (mid & 1) return cout << 0 << '\n', 0;
    mid /= 2;
    cout << bt(0, 0) << '\n';
    return 0;
}