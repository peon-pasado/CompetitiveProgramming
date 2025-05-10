#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n, m, d;
        cin>>n>>m>>d;
        vector<int> a(n);
        for (int i=0; i<n; ++i) {
           cin>>a[i];
        }
        long long res = 0;
        priority_queue<int, vector<int>, greater<int>> q;
        long long sum = 0; 
        for (int i=0; i<n; ++i) {
            res = max(res, sum + a[i] - (i+1)*1ll*d);
            if (a[i] > 0) {
                if (q.size() < m-1) q.push(a[i]), sum += a[i];
                else if (m > 1) {
                    if (q.top() < a[i]) {
                        sum += a[i] - q.top();
                        q.pop();
                        q.push(a[i]);
                    }
                }
            }
        }
        cout << res << '\n';
    }
    return 0;
}