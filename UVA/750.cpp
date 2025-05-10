#include <bits/stdc++.h>
using namespace std;
char arr[9][9];
char Q='1',EMPTY='0';
int ans=0,ci,fi;
bool valid(int f,int c)
{	for(int i=1;i<9;i++)
	{	for(int j=1;j<9;j++)
		{	if(arr[i][j]==Q and (f==i or c==j or (abs(f-i) == abs(c-j))))
			{return false;}
		}
	}
	return true;
}
void backtrack(int col=1)
{	
	if(col==ci)
	{col++;}
	if(col==9)
	{	printf("%2i      ",++ans);
		for(int col=1;col<9;col++)
		{	for(int fil=1;fil<9;fil++)
			{	if(arr[fil][col]==Q)
				{cout<<fil<<" \n"[col==8];break;}
			}
		}
		return;
	}
	
	for(int fil=1;fil<9;fil++)
	{	if(valid(fil,col))
		{	arr[fil][col]=Q;
			backtrack(col+1);
			arr[fil][col]=EMPTY;
		}
	}
}
int main() {
	int ntest;
	cin>>ntest;
	for(int i=0;i<ntest;i++)
	{	cin>>fi>>ci;
		memset(arr,'0',sizeof arr);
		arr[fi][ci]=Q;
		cout<<"SOLN       COLUMN"<<endl;
		cout<<" #      ";
		for(int i=1;i<=8;i++)
		{	cout<<i<<" \n"[i==8];
		}
		cout<<endl;
		backtrack();
		if (i+1 != ntest) cout << endl;
		ans=0;
	}
	return 0;
}