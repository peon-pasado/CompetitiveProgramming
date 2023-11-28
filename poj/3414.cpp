/**
 * @idea backtracking is enough
 * 
**/


#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}

const int N = 101;
int d[N][N];
int n, m, c;
pair<int, int> p[N][N];
void dfs(int x, int y, int L) {
    d[x][y] = L;
    if (x == c || y == c) return;
    int r = min(x, m - y);
    int s = min(n - x, y);
    vector<pair<int, int> > D;
    D.push_back(make_pair(n, y));
    D.push_back(make_pair(x, m));
    D.push_back(make_pair(0, y));
    D.push_back(make_pair(x, 0));
    D.push_back(make_pair(x-r, y+r));
    D.push_back(make_pair(x+s, y-s));
    for (int i=0; i<(int)D.size(); ++i) {
        int a = D[i].first;
        int b = D[i].second;
        if (d[a][b] > L + 1) {
            p[a][b] = make_pair(x, y);
            dfs(a, b, L+1);
        } 
    }
}

void get_path(int x, int y) {
    int k = d[x][y];
    cout << k << '\n';
    vector<pair<int, int> > path;
    pair<int, int> s(x, y);
    path.push_back(s);
    for (int i=0; i<k-1; ++i) {
        s = p[s.first][s.second];
        path.push_back(s);
    }
    int l = 0, r = 0;
    for (int i=(int)path.size()-1; i>=0; --i) {
        int x = path[i].first;
        int y = path[i].second;
        if (x == l && y == m) cout << "FILL(2)"<<'\n';
        else if (x == n && y == r) cout << "FILL(1)"<<'\n';
        else if (x == l && y == 0) cout << "DROP(2)"<<'\n';
        else if (x == 0 && y == r) cout << "DROP(1)"<<'\n';
        else if (x > l) cout << "POUR(2,1)"<<'\n';
        else cout<<"POUR(1,2)"<<'\n';
        l = x; r = y;
    }
}

int main() {
    cin>>n>>m>>c;
    if  (c % gcd(n, m)) return cout << "impossible" << '\n', 0;
    memset(d, 1, sizeof d);
    dfs(0, 0, 0);
    int x = c, y = 0; 
    for (int i=0; i<=n; ++i)
        if (d[x][y] > d[i][c]) {
            x = i;
            y = c;
        }
    for (int i=0; i<=m; ++i)
        if (d[x][y] > d[c][i]) {
            x = c;
            y = i;
        }
    get_path(x, y);
    return 0;
}