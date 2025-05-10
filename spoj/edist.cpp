#include<iostream>
#include<string.h>
#include<algorithm>

using namespace std;


bool vis[3002][3002];
int memo[3002][3002];
string cad1,cad2;

int editDistance(int n,int m){

  if(n==0 or m==0)
    return n+m;
  if(vis[n][m]) return  memo[n][m];

  int &ans=memo[n][m]=1e9;
  ans=min(ans,editDistance(n-1,m-1)+(cad1[n-1]!=cad2[m-1]));
  ans=min(ans,editDistance(n-1,m)+1);
  ans=min(ans,editDistance(n,m-1)+1);
  vis[n][m]=1;
  return ans;
}
int main(){
  int t;
  cin>>t;
  cin.ignore();
  while(t--){
    cin >> cad1;
    cin >> cad2;
    int size1=cad1.size();
    int size2=cad2.size();
    memset(vis,0,sizeof vis);
    cout<<editDistance(size1,size2)<<endl;
  }

  return 0;
}