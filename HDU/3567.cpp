#include <iostream>
#include <string>
using namespace std;

const int N = 3;
int T[N][N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string ds = "udlr";
const int inf = 31 + 2;
char step[inf];
int max_depth;
int px[10], py[10];

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}

int heuristic() {
    int sum = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (T[i][j] > 0) {
                int x = px[T[i][j]];
                int y = py[T[i][j]];
                sum += abs(i - x) + abs(j - y); 
                if (i != x && j != y) {
                    sum += 2 * (i * N + j + 1 == T[x][y] && (i == x || j == y));
                }
            }
        }
    }
    return sum;
}

pair<bool, int> dfs(int x, int y, int depth, int l=-1) {
    int h = heuristic();
    if (depth + h > max_depth) return make_pair(0, depth + h);
    if (h == 0) return make_pair(1, depth);
    int res = inf;
    for (int w=0; w<4; ++w) {
    	int k = (w + 1) % 4;
    	if ((l ^ k) == 1) continue;
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (!valid(nx, ny)) continue;
        step[depth] = ds[k];
        swap(T[x][y], T[nx][ny]);
        pair<bool, int> q = dfs(nx, ny, depth+1, k);
        if (q.first) return q;
        res = min(res, q.second);
        swap(T[x][y], T[nx][ny]);
    }
    return make_pair(0, res);
}   

pair<bool, int> ida_star(int x, int y) {
    max_depth = heuristic();
    while (max_depth != inf) {
        pair<bool, int> q = dfs(x, y, 0);
        if (q.first) return q;
        max_depth = q.second;
    }
    return make_pair(0, inf);
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    string s;
    for (int tc=1; tc<=t; ++tc) {
        cin>>s;
        int x=-1, y=-1;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                if (s[i*N + j] == 'X') {
                    T[x=i][y=j] = 0;
                } else {
                    T[i][j] = s[i*N + j] - '0';
                }
            }
        }
        cin>>s;
        for (int i=0; i<N*N; ++i) {
            int num = (s[i] != 'X') * (s[i] - '0');
            px[num] = i / N;
            py[num] = i % N;
        }
        pair<bool, int> res = ida_star(x, y);
        cout << "Case " << tc << ": ";
        cout << res.second << '\n';
        step[res.second] = 0;
        cout << step << '\n';
    }   
    return 0;
}