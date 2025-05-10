#include <bits/stdc++.h>
using namespace std;
char grilla[105][105];
int dis[105][105];
int stars;
int n,m;
bool vis[105][105];
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
void BFS(int a, int b) {
	queue<pair<int,int>> q;
	q.push(make_pair(a,b));
	for(int i=0 ; i<m ; i++) {
		for (int j=0 ; j<n ; j++) {
			dis[i][j]=-1;
		}
	}
	dis[a][b]=0;
	while(!q.empty()){
		int e=q.front().first;
		int f=q.front().second;
		q.pop();
		
		vis[e][f]=1;
		for(int i=0 ; i<4 ; i++) {
			int g=e+dx[i];
			int h=f+dy[i];
			if(g>=0 && h>=0 && g<m && h<n) {
			
				if(grilla[g][h]=='-' && dis[g][h]==-1){
					dis[g][h]=dis[e][f]+1;
					q.push(make_pair(g,h));
				}	
			}
		}
	}
}
int main() {	
	int conta=1;
	while(cin >> m >> n) {
		if(conta!=1)cout << endl;
		stars=0;
		for(int i=0 ; i<m ; i++) {
			for (int j=0 ; j<n ; j++) {
				vis[i][j]=0;
			}
		}
		for(int i=0 ; i<m ; i++) {
			for(int j=0 ; j<n ; j++) {
				cin >> grilla[i][j];
			}
		}
		for(int i=0 ; i<m ; i++) {
			for(int j=0 ; j<n ; j++) {
				if(!vis[i][j] && grilla[i][j]=='-') {
					BFS(i,j);
					stars++;
				}		
			}
		}
		printf("Case %d: %d",conta,stars );
		
		conta++;
	}
	return 0;
}