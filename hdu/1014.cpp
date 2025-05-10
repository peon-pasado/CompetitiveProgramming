#include <iostream>
#include <iomanip>


using namespace std;
int x, y;
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main(){
while(scanf("%d%d",&x,&y)!=EOF) {
    cout<<setw(10)<<x<<setw(10)<<y<<"    ";
    (gcd(x,y)==1)?printf("Good Choice\n\n"):printf("Bad Choice\n\n");

}


 return 0;
}