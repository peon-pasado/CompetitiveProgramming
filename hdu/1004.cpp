#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
  int n, aux = 0;
  string color,popular;
  while(cin>>n && n){
    map<string,int> balloons;
    for (int i = 0; i < n; i++) {
      /* code */
      cin>>color;
      balloons[color]++;
    }
    map<string,int>::iterator it;
    for (it = balloons.begin(); it != balloons.end(); it++) {
      if (it->second> aux) {
        aux= it->second;
        popular = it->first;
      }
    }
    cout<<popular<<endl;
    aux=0;
  }
return 0;
}