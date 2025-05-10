#include<iostream>
using namespace std;
int repeatDigits(long long a){
	int aux,temp;
	while(a>10){
		aux=a/10;
		temp=a%10;
		while(aux>0){
			if(temp==aux%10){
				return 0;
				break;
			}
			aux/=10;
		}
		a/=10;
	}
	return 1;
}
int main(){
	int t;
	long long a,b,n;
	cin>>t;
	while(t--){
		cin>>n;
		a=0;
		b=1;
		while(a<10000000000){
			if(repeatDigits(b)){
				a=n*b;
				if(repeatDigits(a)){
					cout<<a<<" / "<<b<<" = " <<n<<endl;
				}
			}
			b++;
		}
		
	       if (t) cout << endl;
	}
	return 0;
}