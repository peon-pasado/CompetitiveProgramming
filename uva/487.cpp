#include <bits/stdc++.h>
using namespace std;

int di[] = {0, -1, 1, 0, -1, 1, -1, 1};
int dj[] = {1, 1, 1, -1, -1, -1, 0, 0};

struct cmp{ 
    bool operator()(const string& p, const string& q){
         return p.size() < q.size() or p.size() == q.size() and p < q;
    }
};

const int N = 50;
int t, n;
string T[N];
set<string, cmp> sol; 
string s;

bool valid(int i, int j){
	return i >= 0 and i < n and j >= 0 and j < n;
}


void backtrack(int i, int j){

	if(s.size() >= 3) sol.insert(s);
	
	for(int k = 0; k < 8; ++k){
		int ni = i + di[k];
		int nj = j + dj[k];
			
		if(valid(ni, nj) and T[ni][nj] > s.back()){
			s.push_back(T[ni][nj]);
			backtrack(ni, nj);
			s.pop_back();
		}
	}
}


int main() {
	
	cin >> t;
	while(t--){
		sol.clear();
		cin >> n;
		for(int i = 0; i < n; ++i)
			cin >> T[i];
		
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j){
				s.push_back(T[i][j]);
				backtrack(i, j);
				s.pop_back();
			}
			
		for(string a : sol)		
			cout << a << endl;
		
		if(t) cout << endl;
	}
	
	return 0;
}