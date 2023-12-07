#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;


string s[10];
vector<int> mat(9), fn(9);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string ds = "udlr";
map<vector<int>, int> d;
map<vector<int>, int> p;

void bt(int pos, int depth) {
	//for (int i=0; i<9; ++i) cout << mat[i] << " "; cout << endl;
    d[mat] = depth;
    if (mat == fn) return;
    int ss = 0;
    for (int i=0; i<9; ++i) {
    	if (mat[i] == -1) continue;
    	ss += abs(i / 3 - (mat[i] - 1) / 3);
    	ss += abs(i % 3 - (mat[i] - 1) % 3);
    }
    if (depth + ss >= d[fn]) return;
    for (int i=0; i<4; ++i) {
        int px = pos / 3 + dx[i];
        int py = pos % 3 + dy[i];
        if (px < 0 || py < 0) continue;
        if (px > 2 || py > 2) continue; 
        swap(mat[pos], mat[3*px + py]);
        if (!d.count(mat) || d[mat] > depth + 1) {
            p[mat] = i;
            bt(3*px + py, depth + 1);
        }
        swap(mat[pos], mat[3*px + py]);
    }
}

int main() {
	for (int i=0; i<8; ++i) fn[i] = i+1;
    fn[8] = -1;
    while (cin>>s[0]) {
        for (int i=1; i<9; ++i) cin>>s[i];
        int px = -1;
        for (int i=0; i<9; ++i) {
            if (s[i] != "x") mat[i] = stoi(s[i]);
            else mat[i] = -1, px = i;
        }
        //for (int i=0; i<9; ++i) cout << mat[i] << " "; cout << endl;
        d.clear();
        p.clear();
        d[fn] = 1e9;
        bt(px, 0);
        string res = "";
        int pos = 8;
        while (fn != mat) {
			//for (int i=0; i<9; ++i) cout << fn[i] << " "; cout << endl;
            int id = p[fn];
            int px = pos / 3 - dx[id];
            int py = pos % 3 - dy[id];
            swap(fn[px*3 + py], fn[pos]);
            pos = 3*px + py;
            res += ds[id];
        }
        reverse(res.begin(), res.end());
        cout << res << '\n';
    }

    return 0;
}