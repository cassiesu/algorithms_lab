#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>

using namespace std;

const int INF = 1<<30;
const int DIVISOR = 1000000;
const int MAXH = 500010;

struct Human
{
    int v,l,p;
};

struct Human human[MAXH];
bool v[MAXH];

int T,N,M;
int ans;
int i;
int lft;
int a,b;

inline bool operator<(struct Human x, struct Human y)
{
    return ((x.l<y.l) || (x.l==y.l && x.p > y.p));
}

int main()
{
    int t1,t2;
    int n;
    int ak;
    int tmp;

    std::ios_base::sync_with_stdio(false);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&N,&M);
        n=0;
        memset(v,0,sizeof(v));
        for(i = 1;i <= N;i++)
        {
            scanf("%d %d", &t1,&t2);
            if(t1==0 && t2==0) continue;
            n++;
            human[n].l = t1;
            human[n].p = t2;
        }
        stable_sort(human+1,human+n+1);
        ans = 0;
        lft = 0;
        for(i=2;i<=n;i++)
        {
            if(human[i].l==human[i-1].l && human[i].p==human[i-1].p) v[i]=v[i-1]=1;
        }
        for(i=1;i<=n;i++)
        {
            if(human[i].l>lft+1) break;
            if(human[i].p<=lft) continue;
            if(!v[i]) ans++;
            lft=human[i].p;
        }
        if(lft==M ) printf("%d\n",ans); else printf("0\n");
    }
    return 0;
}

