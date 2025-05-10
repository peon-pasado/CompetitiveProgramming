#include <iostream>
using namespace std;

int main() {
char s[100005];
while (true) { 
scanf("%s", s);
if (s[0] == '0') break;
int sum = 0;
for (int i = 0; s[i]; ++i) sum += s[i] - '0';
sum %= 9;
if (sum == 0) sum = 9;
printf("%d\n", sum);
}
return 0;
}