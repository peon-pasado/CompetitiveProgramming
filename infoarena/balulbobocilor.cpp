/**
 * @author Miguel Mini
 * @tag physics 
 * @idea
 *      - we can see that the boys
 *      meet in D / (v1 + v2) seconds.
 * 
 *      - in this time she moves at 
 *      a speed V.
 *  
 *      - answer: D / (v1 + v2) * V
 * 
 * @complexity O(1)
 */ 

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>
#include <fstream>
#include <stack>
#include <queue>
#include <math.h>
#include <tuple>
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

class Solver {
public:
    struct Node {
        int v, h, g;
    };

    void solveOne(istream& in, ostream& out) {
        int D;
        Node p[2];
        in >> D;
        rep(i, 2) in >> p[i].v >> p[i].h >> p[i].g;
        int V;
        in >> V;
        out << (double)D * V / (p[0].v + p[1].v) << '\n';
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
    string file = "balulbobocilor";
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