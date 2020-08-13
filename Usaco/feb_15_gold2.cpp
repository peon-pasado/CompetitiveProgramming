/**
 * @author Miguel Mini
 * @tag aho-corasick
 * @idea
 *      - We need to keep for each node the suffix of 
 *      longest length that is matcheable, this can be 
 *      done easily in linear time, then we just have 
 *      to carry a list that indicates which node it is
 *      in and we must print the characters that allow 
 *      us to access these nodes in the order they end 
 *      at the end of the algorithm.
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
struct Aho_Corasick {
	const static int sigma = 26;
	const static int LOG = 18;
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
	} T[maxn], A[maxn];
	int p[maxn];
	char inc[maxn];
	bool match[maxn];
	int S[maxn], L[maxn];
	int len[maxn];
	int n = 1;
	Aho_Corasick() {
		memset(S, -1, sizeof S);
		memset(L, -1, sizeof L);
		memset(match, 0, sizeof match);
		p[0] = len[0] = 0;
	}
	void add(const string& s, int r=0) {
		for (auto c : s) {
			if (T[r][c] < 0) {
				len[n] = len[r] + 1;
				T[p[n]=r][inc[n]=c] = n;
				n += 1;
			}
			r = T[r][c]; 
		}
		match[r] = 1;
	}
	int go(int x, char c) {
		if (~A[x][c]) return A[x][c];
		if (~T[x][c]) return A[x][c]=T[x][c];
		return A[x][c] = x ? go(suff(x), c) : 0; 
	}
	int suff(int x) {
		if (~S[x]) return S[x];
		return S[x] = p[x] ? go(suff(p[x]), inc[x]) : 0;
	}
	int super(int x){
        if (~L[x]) return L[x];
        if (!x) return L[x]=0; 
        if (match[suff(x)]) return L[x]=suff(x);
        return L[x]=super(suff(x));
    }
    bool has_match(int x) {
    	return match[x] || super(x);	
    }
	int len_match(int x) {
    	if (match[x]) return len[x];
    	return len[super(x)];
    }
} aut;

int main() {
  freopen("censor.in", "r", stdin);
  freopen("censor.out", "w", stdout);
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string r, s;
  cin >> r;
  int t;
  cin >> t;
  while (t--) {
    cin >> s;
    aut.add(s);
  }
  int n = r.size();
  string res = "";
  int root = 0;
  vector<int> memo(n + 1);
  int ptr = 0;
  for (int i = 0; i < n; ++i) {
    res += r[i];
    root = aut.go(root, r[i]);
    memo[++ptr] = root;
    int len = aut.len_match(root);
    ptr -= len;
    root = memo[ptr];
    while (len--) res.pop_back();
  }
  cout << res << endl;
  return 0;
}
