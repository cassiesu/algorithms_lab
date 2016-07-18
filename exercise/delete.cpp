#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

const int MAXM=4010000; 
const int MAXN=1010000; 

struct Node
{
    int a,b,n;
};

struct node
{
    int num;
    int value;
    node(int x, int y)
    {
        num=x;value=y;
    }
    bool operator<(const node x) const
    {
        return (value<x.value);
    }
};

struct Node edge[MAXM];
int start[MAXN];
bool ff;
int color[MAXN];
int a,b;
int t,n,m,k;
int c;
int g[110];
int peo[110][MAXN];

int search()
{
    int m1,tt;
    int q[MAXN];
    int now,z;
    int t;

    memset(q,-1,sizeof(q));
    now=0;z=1;
    q[z]=0;
    color[0]=1;
    g[1]++;
    peo[1][g[1]]=0;
    while(now<z)
    {
        now++;
        t = q[now];
        tt=start[t];
        while(tt!=0)
        {
            m1=edge[tt].b;
            if(color[m1]==0)
            {
                c=c%k+1;
                if(c==color[t]) 
                {
                    c=c%k+1;
                }
                color[m1]=c;
                g[c]++;
                peo[c][g[c]]=m1;
                z++;
                q[z]=m1;
            }
            tt=edge[tt].n;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); 
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d %d",&n,&m,&k);
        memset(start,0,sizeof(start));
        memset(edge,0,sizeof(edge));
        memset(color,0,sizeof(color));
        memset(g,0,sizeof(g));
        memset(peo,0,sizeof(peo));
        for(int i=1;i<=m;i++)
        {
            scanf("%d %d",&a,&b);
            edge[i].a=a;
            edge[i].b=b;
            edge[i+m].a=b;
            edge[i+m].b=a;
            edge[i].n=start[a];
            start[a]=i;
            edge[i+m].n=start[b];
            start[b]=i+m;
        }
        c=1;
        search();
        ff=0;
        for(int i=0;i<n;i++)
        {
            if(color[i]==0) 
            {
                ff=1;
                break;
            }
        }
        if(n >= k && !ff)
        {
            puts("yes"); 
            for(int i=1;i<=k;i++)
            {
                printf("%d",g[i]);
                for(int j=1;j<=g[i];j++)
                    printf(" %d",peo[i][j]);
                printf("\n");
            }
        }
        else
        {
            puts("no");
        }
    }
    return 0;
}

