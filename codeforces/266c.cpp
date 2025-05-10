#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int sz[2][N];
int A[N][N];
int n;
struct tup{int x, y, z;};
vector<tup> ans;

int zero(int l, int r){
	int in = r;
	for(int i = r; i >= l; --i)
		if(not sz[1][i])
			in  = i;

	return in;
}

int row(int l, int r){
	int in = r;
	for(int i = r; i >= l; --i)
		if(sz[0][i])
			in = i;
	return in;
}	



int main(){

	cin >> n;
	for(int x, y, i = 1; i < n; ++i){
		cin >> x >> y;
		sz[0][x-1]++;
		sz[1][y-1]++;
		A[x-1][y-1] = 1; 
	}	

	for(int i = n-1; i >= 1; --i){
		int nx = zero(0, i);
		if(nx != i){
			ans.push_back({1, i, nx});
			swap(sz[1][i], sz[1][nx]);
			for(int j = 0; j < n; ++j)
				swap(A[j][i], A[j][nx]);

		}

		int ny = row(0, i);
		if(ny != i){
			ans.push_back({0, i, ny});
			swap(sz[0][i], sz[0][ny]);
			for(int j = 0; j < n; ++j)
				swap(A[i][j], A[ny][j]);

			for(int j = 0; j < n; ++j)
				if(A[i][j])
					sz[1][j]--;
		}
	}

	cout << (int)ans.size() << endl;
	for(tup v : ans)
		cout << v.x+1 << " " << v.y+1 << " " << v.z+1 << endl;


	return 0;
}