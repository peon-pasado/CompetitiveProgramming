/**
 * @author Miguel Mini
 * @tag dsu, sorting, offline
 * @idea
 *      - we can sort elements
 *      in non-increasing order.
 *
 *      - maintain a set of
 *      values and merge adjacent
 *      elements with value >= current - D
 *
 *      - we can compute this value
 *      in good time if we use for every
 *      set an array f(): number of elements
 *      with value greater or equal a current value
 *
 *          - maintain f in merge function.
 *
 *          - update f for values with same value
 *          than current.
 *
 * @complexity O(n m \alpha(n) + n m \log(n m))
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 805;
int _id(int x, int y) {
    return x*maxn + y;
}

const int maxm = maxn * maxn;
int lnk[maxm], rnk[maxm];
int f[maxm];
int mat[maxn][maxn];

void init(int x, int y) {
    int id = _id(x, y);
    lnk[id] = id;
    rnk[id] = 0;
    f[id] = 0;
}

int get(int x) {
    return x==lnk[x]?x:lnk[x]=get(lnk[x]);
}

void merge(int x, int y) {
    x = get(x); y = get(y);
    if (x == y) return;
    if (rnk[x] < rnk[y]) swap(x, y);
    rnk[x] += rnk[x]==rnk[y];
    f[x] += f[y];
    lnk[y]=x;
}

using ii = pair<short, short>;
bool vis[maxn][maxn];
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int ans[maxn][maxn];
ii o[maxm];

int main() {
    freopen("mexc.in", "r", stdin);
    freopen("mexc.out", "w", stdout);
    int n, m, d;
    scanf("%d%d%d", &n, &m, &d);
    int siz = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", mat[i]+j);
            init(i, j);
            o[siz++] = {i, j};
        }
    }
    sort(o, o+siz, [&](ii p, ii q) {
        return mat[p.first][p.second] > mat[q.first][q.second];
    });
    auto valid = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < n && y < m;
    };
    int il = 0;
    for (int i = 0, j = 0; i < siz; ++i) {
        while (j < siz && mat[o[j].first][o[j].second]
                          >= mat[o[i].first][o[i].second] - d) {
            for (int k = 0; k < 4; ++k) {
                int nx = o[j].first + dx[k];
                int ny = o[j].second + dy[k];
                if (!valid(nx, ny)) continue;
                if (vis[nx][ny]) {
                    merge(_id(nx, ny), _id(nx-dx[k], ny-dy[k]));
                }
            }
            vis[o[j].first][o[j].second] = 1;
            j += 1;
        }
        int ii = o[i].first, jj = o[i].second;
        int b = get(_id(ii, jj));
        f[b] += 1;
        if (i+1==siz || mat[ii][jj] != mat[o[i+1].first][o[i+1].second]) {
            while (il <= i) {
                int i1 = o[il].first, j1 = o[il].second;
                ans[i1][j1] = f[get(_id(i1, j1))];
                il += 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d ", ans[i][j]);
        }
        puts("");
    }
    return 0;
}