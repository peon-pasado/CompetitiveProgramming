#include <bits/stdc++.h>
using namespace std;

int t, n, m;
struct data{
	int s, f;
};
vector<data> P;

void hanoi(int start, int middle, int final, int n){
	if(P.size() >= m) return;
	if(n == 1){
		P.push_back({start, final});
		return;
	}
	
	hanoi(start, final, middle, n-1);
	P.push_back({start, final});
	hanoi(middle, start, final, n-1);
}

void print(vector<int> p[]){
	for(int j = 0; j < 3; ++j){
		cout << char('A' + j) << "=>"; 
		for(int k = 0; k < p[j].size(); ++k)
			cout << (k == 0 ? "   " : " ") << p[j][k];
		cout << endl;
	}
	cout << endl;	
}

int main() {
	int tc = 1;
	
	while(cin >> n >> m, n+m){
		P.clear();
		cout << "Problem #" << tc++ << endl << endl;
	
		hanoi(0, 1, 2, n);
		
		vector<int> p[3];
		for(int i = n; i >= 1; --i)
			p[0].push_back(i);
		
		print(p);
		for(int i = 0; i < m; ++i){
			int q = p[P[i].s].back(); 
			p[P[i].s].pop_back();
			p[P[i].f].push_back(q);
			
			print(p);
		}
	}
	
	return 0;
}