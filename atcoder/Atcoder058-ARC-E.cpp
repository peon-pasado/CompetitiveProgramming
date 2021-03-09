/**
 * @author Miguel Mini
 * @tags aho-corasick, dp, automaton, brute-force
 * @idea:
 *      - number of pattern is at most 16 x 64 x 16
 *      with ~ 2e5 characters.
 *
 *      - build aho-corasick of patterns and obtain
 *      the aho-corasick automaton
 *
 *      - use dp(position, has_match, AC_state)
 *
 * @complexity O(n x 16 x 64 x 16 x max(x, y, z))
 */

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 1.5e5 + 10;
struct Aho_Corasick {
    const static int sigma = 11;
    struct Trie {
        int nxt[sigma];
        static int ord(char c) {
            if (c < sigma) return c;
            return tolower(c) - 'a';
        }
        int& operator[](char c) {
            return nxt[ord(c)];
        }
        Trie() {
            memset(nxt, -1, sizeof nxt);
        }
    } T[maxn];
    bool match[maxn];
    int S[maxn], L[maxn];
    int len[maxn];
    int n = 1;
    Aho_Corasick() {
        memset(S, -1, sizeof S);
        memset(L, -1, sizeof L);
        memset(match, 0, sizeof match);
        S[0] = L[0] = 0;
        len[0] = 0;
    }
    void add(const vector<int>& s, int r=0) {
        for (auto c : s) {
            if (T[r][c] < 0) {
                len[n] = len[r] + 1;
                T[r][c] = n;
                n += 1;
            }
            r = T[r][c];
        }
        match[r] = 1;
    }

    void build(){
        queue<int> Q;
        Q.emplace(0);
        while(!Q.empty()){
            int u = Q.front();
            Q.pop();
            if(u) L[u] = match[S[u]]? S[u] : L[S[u]];
            for(int i = 0; i < sigma; i++){
                if(~T[u][i]){
                    int v = T[u][i];
                    S[v] = u ? T[S[u]][i] : 0;
                    Q.emplace(v);
                }
                else{
                    T[u][i] = u ? T[S[u]][i] : 0;
                }
            }
        }
    }

    int go(int x, int c){
        return T[x][c];
    }
    bool has_match(int x) {
        return match[x] || L[x];
    }
    int len_match(int x) {
        if (match[x]) return len[x];
        return len[L[x]];
    }
} AC;

vector<vector<int>> solutions;
vector<int> v;
void bt(int sum, int target) {
    if (sum == target) {
        solutions.push_back(v);
        return;
    }
    for (int i = 1; sum + i <= target; ++i) {
        v.push_back(i);
        bt(sum + i, target);
        v.pop_back();
    }
}

vector<vector<int>> patterns;
vector<vector<int>> r[3];
vector<int> t;
void bt2(int pos) {
    if (pos == 3) {
        patterns.push_back(t);
        return;
    }
    for (auto e : r[pos]) {
        for (auto f : e) t.push_back(f);
        bt2(pos+1);
        for (int i = 0; i < e.size(); ++i) t.pop_back();
    }
}

int memo[42][2][130000];
bool vis[42][2][130000];
int n;
int dp(int pos, bool has, int node) {
    if (pos == n) return has;
    if (vis[pos][has][node]) return memo[pos][has][node];
    vis[pos][has][node] = 1;
    int& ans = memo[pos][has][node] = 0;
    for (int i = 1; i <= 10; ++i) {
        int nxt = AC.go(node, i);
        ans += dp(pos+1, has || AC.has_match(nxt), nxt);
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

int main() {
    int x, y, z;
    cin >> n >> x >> y >> z;
    bt(0, x);
    r[0] = solutions;
    solutions.clear();
    bt(0, y);
    r[1] = solutions;
    solutions.clear();
    bt(0, z);
    r[2] = solutions;
    solutions.clear();
    bt2(0);
    for (auto e : patterns) {
        AC.add(e);
    }
    AC.build();
    cout << dp(0, 0, 0) << endl;
    return 0;
}