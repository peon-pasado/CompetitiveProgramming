/**
 * @author Miguel Mini
 * @tag branch_and_bounds
 * @idea
 *      - if N = a0,a1,...,ak then:
 * 
 *           d = sum_{i < (k+1)/2} (a{k-i}-ai) * (10^(k-i) - 10^i)
 *      
 *      - we can notice that: 
 *  
 *          (10^{k-i} - 10^i) > sum_{i < j < (k+1)/2} 9 * (10^{k-j} - 10^j)
 * 
 *      - we can use a branch and bounds approach and 
 *      check if is possible to obtain 0.
 * 
 * @complexity O(18 * number_of_soolutions)
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
#include <climits>
#define sz(x) ((int)x.size())
#define trav(v, x) for (auto v : x)
#define reu(x, y, z) for (int x=y; x<z; ++x)
#define rep(i, n) for (int i = 0; i < n; ++i)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define eb emplace_back
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;

int add(int a, int b, int m=mod) {
    return a+b < m? a+b : a+b-m;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%m;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;
int d;
ll pot[30];


ll bt(int l, int r, ll sum) {  
    if (l > r) return sum == 0;
    if (sum - 10 * (pot[r] - pot[l]) > 0) return 0;
    if (sum + 10 * (pot[r] - pot[l]) < 0) return 0;
    ll ans = 0;
    for (int i = -9; i <= 9; ++i) {
        if (l == r && abs(i) > 0) continue;
        ans += max(0, 9 - abs(i) + (l > 0)) * bt(l+1, r-1, sum - i * (pot[r] - pot[l]));
    }
    return ans;
}


class Solver {
public:
    void solveOne(istream& in, ostream& out) {
        in >> d;
        pot[0] = 1;
        for (int i = 1; i <= 18; ++i) {
            pot[i] = pot[i-1] * 10;
        }
        ll ans = 0;
        for (int i = 1; i <= 18; ++i) {
            ans += bt(0, i, d);
        }
        out << ans << '\n';
    }
    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        //in >> testNumber;
        rep(tc, testNumber) {
            //out << "Case #" << tc+1 << ": ";
            solveOne(in, out);
        }
    }
};

int main() {
    Solver solver;
    string file = "";
    if (!file.empty()) {
      ifstream in(file + ".in");
      ofstream out(file + ".out");
      in.tie(nullptr);
      in.exceptions(in.failbit);
      solver.solve(in, out);
    } else {
      ios_base::sync_with_stdio(false);
      cin.tie(nullptr);
      solver.solve(cin, cout);
    }
    return 0;
}