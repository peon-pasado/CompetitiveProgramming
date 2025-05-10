#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const int N = (6e3) + 5;
vector<int> adj[N];
int memo[N][2];
int in_degree[N];
int n, w[N];

int DP(int u, int ok) {
  int& ret = memo[u][ok];
  if (ret != -1) return ret;
  if (ok) {
    ret = w[u];
    for (int i = 0; i < (int) adj[u].size(); ++i) {
      int v = adj[u][i];
      ret += DP(v, 0);
    }
  } else {
    ret = 0;
    for (int i = 0; i < (int) adj[u].size(); ++i) {
      int v = adj[u][i];
      ret += max(DP(v, 1), DP(v, 0));
    }
  }
  return ret;
}

void graphInit(int n) {
  for (int i = 0; i < n; ++i) {
    adj[i].clear();
    in_degree[i] = 0;
  }
}

void testCase() {
  for (int i = 0; i < n; ++i) {
    scanf("%d", &w[i]);
  }
  graphInit(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v; scanf("%d %d", &u, &v);
    --u; --v;
    adj[v].push_back(u);
    in_degree[u]++;
  }
  for (int i = 0; i < n; ++i) {
    memo[i][0] = -1;
    memo[i][1] = -1;
  }
  
  for (int i = 0; i < n; ++i) {
    if (in_degree[i] == 0) {
      printf("%d\n", max(DP(i, 0), DP(i, 1))); break;
    }
  }
}

// claudio van
int main() {
  int c = 1;
  while (scanf("%d", &n) == 1) {
    testCase(); ++c;
  }
  return 0;
}