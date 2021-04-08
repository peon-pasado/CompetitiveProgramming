/**
 * @author Miguel Mini
 * @tag kmp
 * @idea
 *      - we can prove that
 *      if n \equiv 0 (mod n - b[n])
 *      with b[n] > 0, iff
 *      n is integer periodic.
 * 
 *      - if b[n] == 0 or 
 *      n \equiv 0 (mod n - b[n])
 *      is obvious.
 * 
 *      - in other case, suppose
 *      n != 0 (mod n - b[n]):
 * 
 *      let be a = n - b[n], then
 *      we can see that b[b[n]] is
 *      at least b[n] - a. we can
 *      note that  if:
 *          
 *           b[b[n]] > b[n] - a
 *      
 *      then we can obtain an period
 *      lower than a, this is a 
 *      contradiction.
 */ 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
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
    return a+b < mod? a+b : a+b-mod;
}

int mul(ll a, ll b, int m=mod) {
    return a*b%mod;
}

int ex(int a, int b, int m=mod) {
    int r=1;
    while (b > 0) {
        if (b&1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

const int inf = INT_MAX / 2.2;
const int maxn = 1e6 + 10;
int b[maxn];

class Solver {
public:
    void solveOne(istream& in, ostream& out) {
        string s;
        in >> s;
        int n = s.size();
        b[0] = -1;
        int p = 0;
        for (int i = 1; i <= n; ++i) {
            int& j = b[i] = b[i-1];
            while (j != -1 && s[i-1] != s[j]) j = b[j];
            j += 1;
            if (j > 0 && i % (i - j) == 0) p = max(p, i);
        }
        out << p << '\n';
    }
    void solve(istream& in, ostream& out) {
        out.precision(10);
        out << fixed;
        int testNumber = 1;
        in >> testNumber;
        rep(tc, testNumber) {
            //out << "Case #" << tc+1 << ": ";
            solveOne(in, out);
        }
    }
};

int main() {
    Solver solver;
    string file = "prefix";
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