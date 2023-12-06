/**
 * @idea backtracking
 * 
 * - note that backtracking take and !take, 
 * generate sequences in decreasing lexicographic order.
 * 
 * - use a flag for not repeat values.
*/

#include <bits/stdc++.h>
using namespace std;

int t, n;
vector<int> s;
int x[15];
bool found;
void bt(int pos, int sum, int last, int taked) {
    if (sum > t) return;
    if (pos == n) {
        if (sum == t) {
            found=1;
            //t > 0
            cout<<s[0];
            for (int i=1; i<(int)s.size(); ++i) {
                cout<<'+'<<s[i];
            }
            cout<<'\n';
        }
        return;
    }   
    if (last == x[pos]) {
        if (taked) {
            s.push_back(x[pos]);
            bt(pos+1, sum+x[pos], x[pos], 1);
            s.pop_back();
            bt(pos+1, sum, x[pos], 0);
        } else {
            bt(pos+1, sum, x[pos], 0);
        }
    } else {
        s.push_back(x[pos]);
        bt(pos+1, sum+x[pos], x[pos], 1);
        s.pop_back();
        bt(pos+1, sum, x[pos], 0);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin>>t>>n, n) {
        for (int i=0; i<n; ++i) cin>>x[i];
        cout<<"Sums of "<<t<<":\n";
        found=0;
        bt(0, 0, 0, 0); //x[i] > 0
        if (!found) cout<<"NONE"<<'\n';
    }
    return 0;
}