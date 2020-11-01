/**
 * @author Miguel Mini
 * @tag backtracking, dp, bitmask
 * @idea
 *      - generate all valid configuration,
 *      and run dp for consecutive layers.
 *
 *      - we need optimize valid verification
 *      for two consecutive layers.
**/

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
 
const int maxn = 8;
using ull = unsigned long long;
string mat[2][maxn];
ull dp[maxn][6500];
vector<ull> g[maxn];
ull cst[6500][maxn];
int h;
 
vector<int> dx = {-1, -1, -1, 0, 1, 1, 1, 0};
vector<int> dy = {-1, 0, 1, -1, -1, 0, 1, 1};
 
bool valid(int x, int y) {
    return min(x, y) >= 0 && max(x, y) < 6;
}
 
vector<ull> gen;
ull mask = 0ull;
bool poss(int x, int y) {
    if (x + 1 >= 6 || y + 1 >= 6) return 0;
    ull pot = (1ull << 6 * x + y);
    if (mask & (pot * 195)) return 0;
    return 1;
}
 
void bt(int x, int y) {
    if (x == 6) {
        gen.push_back(mask);
        return;
    }
    if (y == 6) {
        bt(x+1, 0);
        return;
    }
    bt(x, y+1);
    if (poss(x, y)) {
        ull pot = (1ull << ((x<<1) + (x<<2) + y));
        mask ^= pot * 195;
        bt(x, y+1);
        mask ^= pot * 195;
    }
}
 
vector<string> get_mat(ull s) {
    vector<string> ans(6, string(6, '.'));
    int t = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (((s >> i*6+j)&1) && ans[i][j] == '.') {
                ans[i][j] = '0' + t;
                ans[i][j+1] = '0' + t;
                ans[i+1][j] = '0' + t;
                ans[i+1][j+1] = '0' + t;
                t += 1;
            }
        }
    }
    return ans;
}
 
ull get_cost(ull s, int i) {
    vector<string> ms = get_mat(s);
    for (int j = 0; j < 6; ++j) {
        if (mat[0][i][j] == '.') {
            for (int k = 0; k < 6; ++k) 
                if (ms[k][j] != '.') return 0; 
            continue;
        }
        char p = mat[0][i][j];
        bool ok = 0;
        for (int k = 0; k < 6; ++k) {
            if (ms[k][j] != '.') {
                char t = ms[k][j];
                ok = 1;
                if (t == p) break;
                if (!isdigit(t)) return 0;
                ms[k][j] = p;
                for (int l = 0; l < 8; ++l) {
                    int nx = k + dx[l];
                    int ny = j + dy[l];
                    if (!valid(nx, ny)) continue;
                    if (ms[nx][ny] != t) continue;
                    ms[nx][ny] = p;
                }
                break;
            }
        }
        if (!ok) return 0;
    }
    for (int j = 0; j < 6; ++j) {
        if (mat[1][i][j] == '.') {
            for (int k = 0; k < 6; ++k) 
                if (ms[j][k] != '.') return 0; 
            continue;
        }
        char p = mat[1][i][j];
        bool ok = 0;
        for (int k = 5; k >= 0; --k) {
            if (ms[j][k] != '.') {
                char t = ms[j][k];
                ok = 1;
                if (t == p) break;
                if (!isdigit(t)) return 0;
                ms[j][k] = p;
                for (int l = 0; l < 8; ++l) {
                    int nx = j + dx[l];
                    int ny = k + dy[l];
                    if (!valid(nx, ny)) continue;
                    if (ms[nx][ny] != t) continue;
                    ms[nx][ny] = p;
                }
                break;
            }
        }
        if (!ok) return 0;
    }
    set<int> S;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (isdigit(ms[i][j])) S.insert(ms[i][j]);
        }
    }
    ull cst = 1;
    for (int i = 0; i < S.size(); ++i) cst *= 3;
    return cst;
}
 
bool valid2(ull s1, ull s2) {
    for (long long lso = s1 & -s1; s1 > 0; lso = s1 & -s1) {
        ull mask = 195 * lso;
        if (!(s2 & mask)) return 0;
        s1 ^= mask;
    }
    return 1;
}
 
int main() {
    cin >> h;
    for (int i = 0; i < 2; ++i)
        for (int j = h-1; j >= 0; --j)
            cin >> mat[i][j];
    bt(0, 0);
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < gen.size(); ++j) {
            cst[j][i] = get_cost(gen[j], i);
            if (cst[j][i] > 0) g[i].emplace_back(j);
        }
    for (int i = 0; i < gen.size(); ++i) dp[0][i] = cst[i][0];
    for (int i = 0; i + 1 < h; ++i)
        for (int k : g[i])
            for (int j : g[i+1])
                if (valid2(gen[j], gen[k])) {
                    dp[i+1][j] += cst[j][i+1] * dp[i][k];
                }
    cout << accumulate(dp[h-1], dp[h-1] + 6500, 0ull) << '\n';
    return 0;
}
