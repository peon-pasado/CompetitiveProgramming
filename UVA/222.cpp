#include <bits/stdc++.h>
using namespace std;

const double inf = 1e18;
double cap_fuel, mpg;
int n;
double d[60];
double c[60];
double ans;

void bt(int pos, double total_cost) {
    if (total_cost > ans) return;
    if (pos == n || d[pos] + cap_fuel * mpg >= d[n+1]) {
        ans = total_cost;
        return;
    }
    for (int i=pos+1; i<=n; ++i) {
        double len = d[i] - d[pos];
        if ((2 * len >= cap_fuel * mpg || d[pos] + cap_fuel * mpg < d[i+1]) && len <= cap_fuel * mpg) {
            bt(i, total_cost + 2 + len / mpg * c[i] / 100.0);
        }
    }
}

int main() {
    cout.precision(2);
    cout<<fixed;
    int tc=1;
    double df;
    while (cin>>df, df>=0) {
        cin>>cap_fuel>>mpg>>c[0]>>n;
        d[n+1] = df;
        for (int i=1; i<=n; ++i) {
            cin>>d[i]>>c[i];
        }
        ans = inf;
        c[n+1] = 0;
        bt(0, 0);
        cout << "Data Set #" << tc++ << '\n';
        cout << "minimum cost = $" << c[0] + ans << '\n';
    }
    return 0;
}