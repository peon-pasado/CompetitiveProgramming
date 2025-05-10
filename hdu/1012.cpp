#include<iostream>

using namespace std;
  int arr[10];
  double ans[10];
///dfdfdfdf
int main(){

  printf("n e\n");
  printf("- -----------\n");

  arr[0]=1;
  ans[0]=1;
  for(int i=1;i<10;i++)
    arr[i]=i*arr[i-1];
  for(int i=1;i<10;i++)
    ans[i]+=ans[i-1]+(1.0/arr[i]);

  printf("0 1\n");
  printf("1 2\n");
  printf("2 2.5\n");
  for(int i=3;i<10;i++){
    if(i>2)
      printf("%d %.9lf\n",i,ans[i]);
  }
  return 0;
}