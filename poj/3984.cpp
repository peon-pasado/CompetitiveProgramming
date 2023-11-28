/**
 * @idea:
 *  simule with backtracking every path.
*/

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int N = 5;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
int b[N][N];

vector<pair<int, int> > path, solution;
bool vis[N][N];
void dfs(int i, int j, int d) {
    if (i==4&&j==4) {
        if (solution.empty() || d < (int)solution.size()) {
            solution = path;
        }
        return;
    }
    vis[i][j]=1;
    for (int k=0;k<4;++k) {
        int ni = i+dx[k];
        int nj = j+dy[k];
        if (ni<0||nj<0||ni>=N||nj>=N||b[ni][nj]||vis[ni][nj]) continue;
        path.push_back(make_pair(ni, nj));
        dfs(ni, nj, d+1);
        path.pop_back();
    }
    vis[i][j]=0;
}

int main() {
    for (int i=0;i<5;++i)
        for (int j=0;j<5;++j) {
            cin>>b[i][j];
        }
    path.push_back(make_pair(0, 0));
    dfs(0, 0, 1);
    for (int i=0;i<(int)solution.size();++i) {
        cout << "(" << solution[i].first << ", " << solution[i].second << ")" << '\n';
    }
    return 0;
}