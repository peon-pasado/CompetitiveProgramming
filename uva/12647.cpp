#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
#define bon 1000010
using namespace std;
int cover[bon<<2];
int f[maxn<<2],ans[maxn<<2];
struct line
{
    int x1,y1,x2,y2;
    bool operator<(const line &t)const
    {
        return y1<t.y1;
    }
} li[maxn<<2];

void pushdown(int rt)
{
    if(cover[rt]>=0)
    {
        cover[rt<<1]=cover[rt<<1|1]=cover[rt];
        cover[rt]=-1;
    }
}

int query(int x,int l,int r,int rt)
{
    if(cover[rt]>=0) return cover[rt];
    int mid=(l+r)>>1;
    pushdown(rt);
    if(x<=mid)return query(x,l,mid,rt<<1);
    else return query(x,mid+1,r,rt<<1|1);
}

void update(int L,int R,int i,int l,int r,int rt)
{
    if(L<=l&&R>=r)
    {
        cover[rt]=i;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(rt);
    if(L<=mid)update(L,R,i,l,mid,rt<<1);
    if(R>mid)update(L,R,i,mid+1,r,rt<<1|1);
}
int n,q,xx;
void solve(int x)
{
    int k=query(x,0,bon,1);
    if(li[k].y1!=li[k].y2)x=ans[k];
    if(f[k]==n)printf("%d\n",x);
    else printf("%d %d\n",x,li[f[k]].y1);
}

int main()
{
    while(scanf("%d%d",&n,&q)!=EOF)
    {
        memset(cover,-1,sizeof cover);
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%d%d",&li[i].x1,&li[i].y1,&li[i].x2,&li[i].y2);
            if(li[i].y1<li[i].y2)
            {
                swap(li[i].x1,li[i].x2);
                swap(li[i].y1,li[i].y2);
            }
        }
        li[n].x1=0,li[n].x2=bon,li[n].y1=bon+1,li[n].y2=bon+1;
        sort(li,li+n+1);
        for(int i=n; i>=0; i--)
        {
            if(li[i].y1==li[i].y2) f[i]=i;
            else
            {
                int k=query(li[i].x1,0,bon,1);
                f[i]=f[k];
                if(li[k].y1==li[k].y2) ans[i]=li[i].x1;
                else ans[i]=ans[k];
            }
            int l=li[i].x1,r=li[i].x2;
            if(l>r)swap(l,r);
            update(l,r,i,0,bon,1);
        }
        while(q--)
        {
            scanf("%d",&xx);
            solve(xx);
        }
    }
    return 0;
}