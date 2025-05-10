#include <iostream>
using namespace std;

int di[] = {0, 0, -1};
int dj[] = {1, -1, 0};
string dd[] = {"right", "left", "forth"};
const int N = 500;
string T[N];
int n, m, t;

//depth first search
string p = "IEHOVA#";


bool valid(int i, int j){
	return i >= 0 and i < n and j >= 0 and j < m;
}

void dfs(int i, int j, int h){
	
	if(h == p.size()){
		cout << endl;
		return;
	}
	else if(h) cout << " ";
	
	for(int k = 0; k < 3; ++k){
		int ni = i + di[k];
		int nj = j + dj[k];
		
		if(valid(ni,nj) and T[ni][nj] == p[h]){
			cout << dd[k];
			dfs(ni, nj, h+1);
		}
	}	
	
}

int main() {
	
	cin >> t;
	while(t--){
		cin >> n >> m;
		for(int i = 0; i < n; ++i)
			cin >> T[i];

		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(T[i][j] == '@')
					dfs(i, j, 0);
	}

	return 0;
}