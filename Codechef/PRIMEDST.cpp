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
#include <complex>
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
using ii = pair<ll, ll>;
using vi = vector<int>;
using vii = vector<ii>;
const int mod = 1e9 + 7;
const int inf = 1.2e9;
const int maxn = 1e5 + 10;
bool composite[maxn];
vi prime;

void sieve(int n) {
  composite[1] = 1;
  re(i, 2, n+1) {
    if (!composite[i]) {
      prime.eb(i);
    }
    trav(p, prime) {
      if (p * i > n) break;
      composite[p * i] = 1;
      if (i % p == 0) break;
    }
  }
}

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
  int n = a.size();

  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1)
      j ^= bit;
    j ^= bit;

    if (i < j)
      swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : 1);
    cd wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i+j], v = a[i+j+len/2] * w;
        a[i+j] = u + v;
        a[i+j+len/2] = u - v;
        w *= wlen;
      }
    }
  }

  if (invert) {
    for (cd & x : a)
      x /= n;
  }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size())
    n <<= 1;
  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; i++)
    fa[i] *= fb[i];
  fft(fa, true);

  vector<ll> result(n);
  for (int i = 0; i < n; i++)
    result[i] = round(fa[i].real());
  return result;
}

struct CentroidDecomposition {
    vector<vector<int>> T;
    vector<int> siz, P, rank;
    vector<bool> block;
    vector<vector<int>> dist;
    vector<int> res;
    int root;
    CentroidDecomposition(int n):
    T(n)
    , siz(n)
    // , P(n, -1)
    , block(n)
    // , rank(n)
    , root(0)
    //, dist((int)log2(n) + 1, vector<int>(n))
    //, res(n, inf)
    {}
    void addEdge(int a, int b) {
      T[a].emplace_back(b);
      T[b].emplace_back(a);
    }
    bool valid(int x, int p) {
      return x != p and not block[x];
    }
    int dfs(int x, int p=-1) {
      siz[x] = 1;
      for (int v : T[x]) {
        if (valid(v, p)) {
          siz[x] += dfs(v, x);
        }
      }
      return siz[x];
    }
    int get_centroid(int x, int p, int n) {
      for (int v : T[x]) {
        if (valid(v, p) and siz[v] > n>>1) {
          return get_centroid(v, x, n);
        }
      }
      return x;
    }
    void calc_dist(int x, int r, int p=-1, int h=0) {
      dist[r][x] = h;
      for (int v : T[x]) {
        if (valid(v, p)) {
          calc_dist(v, r, x, h+1);
        }
      }
    }
    ii decompose(int x, int p=-1, int r=0) {
      int n = dfs(x);
      int cen = get_centroid(x, -1, n);
      //calc_dist(cen, r);
      //P[cen] = p;
      auto add = [](ii p, ii q) {
        return ii(p.first+q.first, p.second+q.second);
      };
      ii ans = solve(cen, 0);
      block[cen] = 1;
      //rank[cen] = r;
      trav(v, T[cen]) {
        if (block[v]) continue;
        ii temp = solve(v, 1);
        temp.first = -temp.first;
        temp.second = -temp.second;
        ans = add(ans, temp);
      }
      for (auto v : T[cen]) {
        if (block[v]) continue;
        ans = add(ans, decompose(v, cen, r+1));
      }
      return ans;
    }
    ii solve(int x, int h) {
      vector<ll> a = {0};
      get_dist(x, -1, h, a);
      vector<ll> b = a;
      //reverse(b.begin(), b.end());
      int n = sz(a);
      a = multiply(a, b);
      ii res = {0ll, 0ll};
      re(i, 1, sz(a)) {
        int num = i;
        if (!composite[num]) res.first += a[i];
        res.second += a[i];
      }
      return res;
    }
    void get_dist(int x, int p, int h, vector<ll>& a) {
      if (h >= sz(a)) a.eb(0);
      a[h] += 1;
      trav(v, T[x]) {
        if (!valid(v, p)) continue;
        get_dist(v, x, h+1, a);
      }
    }
};

class PRIMEDST {
public:
    void solveOne(istream& in, ostream& out) {
      sieve(1e5 + 2);
      int n;
      in >> n;
      CentroidDecomposition tree(n);
      re(i, 0, n-1) {
        int a, b;
        in >> a >> b;
        tree.addEdge(a-1, b-1);
      }
      ii res = tree.decompose(tree.root);
      out << res.first * 1. / res.second << endl;
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
