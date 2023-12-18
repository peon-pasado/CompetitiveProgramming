/**
 * @idea backtracking, IDA-star, math
 * 
 * - we can simulate movements with backtracking.
 * 
 * - to minimize we can bound the max number of movements
 * with iterative deepening technique.
 * 
 * - we can use a-star heuristics (manhattan distance + 2 x number of linear conflicts).
 * 
 * - board with no solution are these with odd number of inversions.
 *  
**/
#include <iostream>
#include <string>
using namespace std;

const int N = 3;
int T[N][N];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string ds = "udlr";
const int inf = 31 + 1;
char step[inf];
int max_depth;

bool valid(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}

int heuristic() {
    int sum = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (T[i][j] > 0 && T[i][j] != i*N+j+1) {
                int x = (T[i][j] - 1) / N;
                int y = (T[i][j] - 1) % N;
                sum += abs(i - x) + abs(j - y); 
                sum += 2 * (i * N + j + 1 == T[x][y] && (i == x || j == y));
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
    for (int k=0; k<4; ++k) {
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

bool is_possible() {
    int inv_cnt = 0;
    for (int i=0; i<N*N; ++i) 
        for (int j=i+1; j<N*N; ++j)
            inv_cnt += (T[i/N][i%N] && T[j/N][j%N] && T[i/N][i%N] > T[j/N][j%N]);
     return inv_cnt % 2 == 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s[9];
    while (cin>>s[0]) {
        for (int i=1; i<N*N; ++i) cin>>s[i];
        int x=-1, y=-1;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                if (s[i*N + j] == "x") {
                    T[x = i][y = j] = 0;
                } else {
                    T[i][j] = stoi(s[i*N + j]);
                }
            }
        }
        pair<bool, int> res = {-1, -1};
        if (is_possible() && (res = ida_star(x, y), res.first)) {
            step[res.second] = 0;
            cout << step << '\n';
        } else {
            cout << "unsolvable" << '\n';
        }
    }   
    return 0;
}