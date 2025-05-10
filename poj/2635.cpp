#include <cstdio>
#include <cstring>
int pri[1000001],top=0,x;
bool phi[1000001];
char s[101];
inline void init()
{
    for (int i=2;i<=1000000;++i)
    {
        if (!phi[i]) pri[++top]=i;
        for (int j=1;j<=top;++j)
        {
            if (pri[j]*i>=1000000) break;
            phi[pri[j]*i]=true;
            if (i%pri[j]==0) break;
        }
    }
}
int main()
{
    init();
//  printf("yes\n");
    while (scanf("%s%d",s+1,&x)&&x)
    {
        int l=strlen(s+1);
        int flag=0;
        for (int i=1;i<=top&&pri[i]<x;++i)
        {
            int n=0,j;
            for (j=1;j+2<=l;j+=3)
                (n=n*1000+((s[j]-'0')*100+(s[j+1]-'0')*10+(s[j+2]-'0')))%=pri[i];
            if (j==l-1) (n=n*100+(s[j]-'0')*10+(s[j+1]-'0'))%=pri[i];
            if (j==l) (n=n*10+s[j]-'0')%=pri[i];
            if (!n)
            {
                flag=1;
                printf("BAD %d\n",pri[i]);
                break;
            }
        }
        if (!flag) printf("GOOD\n");
    }
}