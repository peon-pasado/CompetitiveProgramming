#include <bits/stdc++.h>
using namespace std;
const int MAX=1100;
long long N,M,res;
int mat[MAX][MAX], S[MAX][MAX],ans[MAX][MAX],tc=1;
 
int main(){
 int t = 0;
	while(cin >> N >> M) {
if(t++) cout << endl;
		res=0;
		for(int i=0;i<N;i++){
			for (int j=0; j<N; j++) cin>>mat[i][j];
		}
		for(int i=0; i<N; i++){
    		for(int j=0; j<N; j++){
        		S[i][j] = mat[i][j];
        		if(i > 0) S[i][j] += S[i-1][j];
        		if(j > 0) S[i][j] += S[i][j-1];
       		 	if(i > 0 and j > 0) S[i][j] -= S[i-1][j-1];
       		 }
       	}
       	for(int i=M-1;i<N;i++){
			for (int j=M-1; j<N; j++){
				ans[i][j]=S[i][j];
				if(i-M>=0) ans[i][j]-=S[i-M][j];
				if(j-M>=0) ans[i][j]-=S[i][j-M];
				if(i-M>=0&&j-M>=0) ans[i][j]+=S[i-M][j-M];
				cout<<ans[i][j]<<endl;
				res+=ans[i][j];
			}
		}
		cout<<res << endl; 
    }
    return 0;
}