#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
int a[maxn];
int b[maxn];
string s;
using dpq = vector<pair<priority_queue<int, vector<int>, greater<int>>, priority_queue<int>>>;
dpq P;

int main() {
    int n;
    cin>>n;
    for (int i=0; i<n; ++i) cin>>a[i];
    int m;
    cin>>m;
    for (int i=0; i<m; ++i) cin>>b[i];
    cin>>s;
    P.resize(1);
    bool left = 1;
    for (int i=0; i<m; ++i) {
        if (s[i] == 'S') {
            if (!left) P.resize(P.size() + 1);
            P.back().first.push(b[i]);
        } else {
            P.back().second.push(b[i]);
            left = 0;
        }
    }
    const int mod = 1e9;
    long long v = 0;
    for (int i=0; i<n; ++i) {
        if (i > 0) a[i] = (a[i] + v) % mod;
        for (auto& e : P) {
            if (!e.first.empty()) {
                e.first.push(a[i]);
                a[i] = e.first.top(); e.first.pop();
            }
            if (!e.second.empty()) {
                e.second.push(a[i]);
                a[i] = e.second.top(); e.second.pop();
            }
        }
        v += a[i];
        cout << v << " \n"[i+1==n];
        dpq R;
        R.push_back(move(P[0]));
        for (int j=1; j<P.size(); ++j) {
            if (!P[j].second.empty() && P[j].first.top() >= P[j].second.top()) {
                if (R.back().second.size() < P[j].second.size()) {
                    swap(R.back().second, P[j].second);
                }
                while (!P[j].second.empty()) {
                    R.back().second.push(P[j].second.top());
                    P[j].second.pop();
                }
                if (j + 1 < P.size()) {
                    if (P[j].first.size() > P[j+1].first.size()) {
                        swap(P[j].first, P[j+1].first);
                    }
                    while (!P[j].first.empty()) {
                        P[j+1].first.push(P[j].first.top());
                        P[j].first.pop();
                    }
                } else {
                    R.push_back(move(P[j]));
                }
            } else {
                R.push_back(move(P[j]));
            }
        }
        swap(R, P);
    }
    return 0;
}