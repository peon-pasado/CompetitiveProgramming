/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Miguel Mini
 * @tag dsu on trees, tree, dfs, ladder decomposition, BIT, offline, heavy-light decomposition
 * @idea
 *      - we can use dsu on trees or ladder decomposition on the son with the highest height.
 *      - we use the idea of Arpa (sack) to keep or not a tree and we use a fenwick tree.
 *      - if we work on O(sum of heights) of the children who are not the highest, our
 *      complexity is O(n x BIT_update)
 *          - proof:
 *                  Suppose we put a token on each node of the tree, and move the token
 *                  to the father of the first ancestor who is not the highest child.
 *                  Let's see that the number of tokens in each node is the number of
 *                  operations that node does, the sum of these quantities is less than
 *                  or equal to n. QED
 *
 * @complexity O(n \log n)
 */

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <list>
#include <forward_list>
#define sz(x) (int)x.size()
#define trav(v, x) for (auto v : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define set_to(x, v) fill(all(x), v)
#define eb emplace_back
#define lso(x) ((x)&-(x))
#define mset(m ,v) memset(m, v, sizeof(m))
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;
const int inf = 1.2e9;
const int maxN = 250 * 1000 + 5;
short c[maxN];
forward_list<int> q[maxN];
vii queries[maxN];
vi g[maxN];
int len[maxN];
int ans[maxN<<1];
int big[maxN];
int ft[maxN];

void update(int node, int add) {
  while (node < maxN) {
    ft[node] += add;
    node += node&-node;
  }
}

int query(int node) {
  int response = 0;
  while (node > 0) {
    response += ft[node];
    node -= node&-node;
  }
  return response;
}

void pre_dfs(int x) {
  big[x] = -1;
  len[x] = 0;
  trav(v, g[x]) {
    pre_dfs(v);
    len[x] = max(len[x], len[v] + 1);
    if (big[x] == -1 || len[big[x]] < len[v]) {
      big[x] = v;
    }
  }
}

void dfs(int x, int h, bool keep) {
  trav(v, g[x]) {
    if (v == big[x]) continue;
    dfs(v, h + 1, 0);
  }
  if (big[x] != -1) {
    dfs(big[x], h + 1, 1);
    swap(q[x], q[big[x]]);
  }
  q[x].push_front(c[x]);
  update(h, c[x]);
  trav(v, g[x]) {
    if (v == big[x]) continue;
    auto l = q[x].begin(); ++l;
    int i = 1;
    trav(t, q[v]) {
      *l += t;
      update(h + i, t);
      i += 1;
      ++l;
    }
  }
  trav(e, queries[x]) {
    ans[e.second] = query(min(maxN - 1, e.first + h));
  }
  if (keep == 0) {
    int i = 0;
    trav(v, q[x]) {
      update(h + i, -v);
      i += 1;
    }
  }
}

class Arb {
public:
    void solveOne(istream& in, ostream& out) {
      int n;
      in >> n;
      re(i, 1, n+1) {
        in >> c[i];
      }
      re(i, 2, n+1) {
        int p;
        in >> p;
        g[p].eb(i);
      }
      int m;
      in >> m;
      re(i, 0, m) {
        int v, d;
        in >> v >> d;
        queries[v].eb(d, i);
      }
      pre_dfs(1);
      dfs(1, 1, 1);
      re(i, 0, m) {
        out << ans[i] << '\n';
      }
    }

    void solve(istream& in, ostream& out) {
      int testNumber = 1;
      //in >> testNumber;
      re(tc, 1, testNumber+1) {
        //out << "Case #" << tc << ": ";
        solveOne(in, out);
      }
    }
};


int main() {
  freopen("arb.in", "r", stdin);
  freopen("arb.out", "w", stdout);
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  Arb solver;
  std::istream& in(std::cin);
  std::ostream& out(std::cout);
  solver.solve(in, out);
  return 0;
}