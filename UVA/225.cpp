#include<iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;
int wesn[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

char array_wesn[]="wesn";

void printArray(char a[],int n){
	for(int i=0;i<n;i++){
		cout<<a[i];
	}
}
bool comp_block(int x,int y,int x1,int y1,int block1,int block2){
	if(x==x1)
		if(x==block1&&((block2>=y&&block2<=y1)||(block2<=y&&block2>=y1)))
			return false;
	if(y==y1)
		if(y==block2&&((block1>=x&&block1<=x1)||(block1<=x&&block1>=x1)))
			return false;
	return true;
}

char tp[10000][100];
int T;
bool vis[2000][2000];
const int O = 1000;
void road(int x,int y,int numero,int movimiento,char road_array[],int comp_usado[],int num_block, int blocks[],int contador[]){
    int aux1,aux2,x1,y1,comprobar;
	if(movimiento==numero+1){
		if(x==0&&y==0){
            for (int i=0; i<numero; ++i) tp[T][i] = road_array[i];
            tp[T][numero] = 0;
            T++;
			//printArray(road_array,numero);
			//cout<<endl;	
			contador[0]++;
			return;
		}
		return;
	}
	else if(movimiento==1||(x!=0||y!=0)){
        if (vis[O + x][O + y]) return;
        vis[O + x][O + y] = 1;
        //if (ss.count({x, y})) return;
        //ss.insert({x, y});
		aux1=comp_usado[0];
		aux2=comp_usado[1];
		for(int i=0;i<4;i++){
			comprobar=1;	
			if(comp_usado[i/2]==0){
				x1=x+movimiento*wesn[i][0];
				y1=y+movimiento*wesn[i][1];
				for(int j=0;j<num_block;j++){
					if(comp_block(x,y,x1,y1,blocks[2*j],blocks[2*j+1])==0)
						comprobar=0;
				}
				if(comprobar){
					x+=movimiento*wesn[i][0];
					y+=movimiento*wesn[i][1];
					comp_usado[i/2]=1;
					comp_usado[1-i/2]=0;
					road_array[movimiento-1]=array_wesn[i];
					road(x,y,numero,movimiento+1,road_array,comp_usado,num_block,blocks,contador);
					x-=movimiento*wesn[i][0];
					y-=movimiento*wesn[i][1];
				}
				
			}
			comp_usado[0]=aux1;
			comp_usado[1]=aux2;	
		}
        vis[O + x][O + y] = 0;
	}
}
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
	int x,y,numero,t;
	cin>>t;
	while(t--){
		int contador[1]={0},numero_block,usado[2]={0,0};
		x=y=0;
		cin>>numero;
		char road_array[numero];
		for(int i=0;i<numero;i++)
			road_array[numero]='\0';
		cin>>numero_block;
		int blocks[numero_block*2];
		for(int i=0;i<2*numero_block;i++)
			cin>>blocks[i];
        T=0;
		road(x,y,numero,1,road_array,usado,numero_block,blocks,contador);
        vector<int> id(T);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](int i, int j) {
            return strcmp(tp[i], tp[j]) < 0;
        });
        for (int i=0; i<T; ++i) {
            printArray(tp[id[i]], numero);
            cout << '\n';
        }
		cout<<"Found "<<contador[0]<<" golygon(s)."<<'\n'<<'\n';
	}
	
	return 0;
}