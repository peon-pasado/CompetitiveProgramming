#include "swap.h"
#include <vector>

#include <bits/stdc++.h>
#define sz(v) static_cast<int>(v.size())
#define clear_fit(v) v.clear(), v.shrink_to_fit()
#define all(v) v.begin(), v.end()
#define unique(v) v.erase(unique(all(v)), v.end())
#define fast_io cin.tie(nullptr)->sync_with_stdio(false)

using namespace std;

const int maxn = 2e5 + 10;
int st[19][maxn];
bool is_path[maxn];
int ep[maxn][2];
int h[maxn];

struct reachability_tree {
    vector<vector<int>> g;
    vector<int> pi;
    vector<int> val;
    vector<int> ord;
    vector<pair<int, int>> range;
    int T;

    reachability_tree() {}

    reachability_tree(int n) {
        g.resize(n);
        val.resize(n);
        pi.resize(n);
        ord.resize(n);
        iota(all(pi), 0);
        for (int i=0; i<n; ++i) {
          is_path[i] = 1;
          ep[i][0] = ep[i][1] = i;
        }
    }

    int get(int x) {
        return x != pi[x] ? pi[x] = get(pi[x]) : x;
    }

    void merge_set(int x, int a, int b, int c, int d) {
        if (!is_path[a]) {
          is_path[x] = 0;
          return;
        }
        if (!is_path[b]) {
          is_path[x] = 0;
          return; 
        }

        for (int i=0; i<2; ++i)
          for (int j=0; j<2; ++j)
            if (ep[a][i] == c) {
              if (ep[b][j] == d) {
                  is_path[x] = 1;
                  ep[x][0] = ep[a][1-i];
                  ep[x][1] = ep[b][1-j];
                  return;
              }
            }
        is_path[x] = 0;
    }

    void merge(int x, int y, int time) {
        int u = x, v = y;
        x = get(x);
        y = get(y);
        if (x == y) {
          if (is_path[x]) {
              val[x] = time;
              is_path[x] = 0;
          }
          return;
        }
        int new_node = g.size();
        g.resize(g.size() + 1);
        pi[x] = pi[y] = new_node;
        val.push_back(time);
        pi.push_back(new_node);
        merge_set(new_node, x, y, u, v);
        g[new_node].push_back(x);
        g[new_node].push_back(y);
    }

    void build(vector<pair<pair<int, int>, int>> edges) {
        //sort(all(edges), [](auto p, auto q) {
        //    return p.first < p.second;
        //});
        for (auto e : edges) {
            merge(e.first.first, e.first.second, e.second);
        }
    }

    void dfs(int x, int p=-1) {
        st[0][x] = p==-1?x:p;
        h[x] = p==-1?0:h[p]+1;
        for (int k=1; k<=18; ++k)
            st[k][x] = st[k-1][st[k-1][x]];
        for (auto v : g[x]) {
            dfs(v, x);
        }
    }

    void make_tree() {
        T = 0;  
        for (int i = 0; i < g.size(); ++i) {
            if (pi[i] == i) {
                dfs(i);
            }
        }
    }

    int get_value(int x, int y) {
        if (h[x] > h[y]) swap(x, y);
        for (int k=18; k >= 0; --k) {
            if (h[st[k][y]] >= h[x]) {
              y = st[k][y];
            }
        }
        if (x != y) {
          for (int k=18; k>=0; --k) {
            if (st[k][x] != st[k][y]) {
              x = st[k][x];
              y = st[k][y];
            }
          }
          x = st[0][x];
        }
        if (!is_path[x]) return val[x];
        for (int k=18; k>=0; --k) {
            if (is_path[st[k][x]]) {
                x = st[k][x];
            }
        }
        if (is_path[st[0][x]]) return -1;
        return val[st[0][x]];
    }
} dsu;


void init(int N, int M, std::vector<int> U, std::vector<int> V, std::vector<int> W) {
  vector<pair<int, int>> id(M);
  for (int i=0; i<M; ++i) id[i] = {W[i], i};
  sort(all(id));
  dsu = reachability_tree(N);
  for (auto e : id) {
    dsu.merge(U[e.second], V[e.second], W[e.second]);
  }
  dsu.make_tree();
}

int getMinimumFuelCapacity(int X, int Y) {
  return dsu.get_value(X, Y);
}