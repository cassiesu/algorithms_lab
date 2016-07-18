#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>

using namespace std;

const int MAXH=110;
const int MAXM=11000; 

struct Node
{
    int a,b,w,n;
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
        return (value>x.value) || (value==x.value && num>x.num);
    }
};

struct Node edge[MAXM];
struct Node edge2[MAXM*2];
int fat[MAXH];
int son[MAXH];
bool ff;
int sum,ans,ans2;
int start[MAXH];
int dis[MAXH];

bool operator<(const struct Node x,const struct Node y)
{
    return x.w<y.w;
}

int father(int x)
{
    return x==fat[x] ? x : father(fat[x]);
}

bool joint(struct Node x)
{
    int t1,t2;
    t1=father(x.a);
    t2=father(x.b);
    if(t1==t2) return 0;
    else
    {
        if(son[t1]>=son[t2])
        {
            fat[t2]=t1;
            son[t1]+=son[t2];
        }
        else
        {
            fat[t1]=t2;
            son[t2]+=son[t1];
        }
    }
    return 1;
}

int search()
{
    int t1,t2;
    struct node tt(0,0);
    priority_queue<struct node> q;

    memset(dis,-1,sizeof(dis));
    dis[0]=0;
    while(!q.empty()) q.pop();
    q.push(node(0,0));
    while(!q.empty())
    {
        tt=q.top();
        q.pop();
        t1=tt.num;
        t2=start[t1];
        while(t2!=0)
        {
            if(dis[edge2[t2].b]==-1 || dis[t1]+edge2[t2].w<dis[edge2[t2].b])
            {
                dis[edge2[t2].b]=dis[t1]+edge2[t2].w;
                q.push(node(edge2[t2].b,dis[edge2[t2].b]));
            }
            t2=edge2[t2].n;
        }
    }
}

int main()
{
    int a,b,w;
    int t,n,m;
    int tmp;

    ios_base::sync_with_stdio(false); 
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;i++)
        {
            fat[i]=i;
            son[i]=1;
        }
        memset(start,0,sizeof(start));
        for(int i=1;i<=m;i++)
        {
            scanf("%d %d %d",&a,&b,&w);
            edge[i].a=a;
            edge[i].b=b;
            edge[i].w=w;
            edge2[i].a=a;
            edge2[i].b=b;
            edge2[i].w=w;
            edge2[i+m].a=b;
            edge2[i+m].b=a;
            edge2[i+m].w=w;
            edge2[i].n=start[a];
            start[a]=i;
            edge2[i+m].n=start[b];
            start[b]=i+m;
        }
        sort(edge+1,edge+m+1);
        sum=0;
        ans=0;
        for(int i=1;i<=m;i++)
        {
            if(joint(edge[i]))
            {
                sum++;
                ans += edge[i].w;
                if(sum==n-1)
                {
                    break;
                }
            }
        }
        printf("%d ",ans);
        ans2=0;
        search();
        for(int i=0;i<n;i++)
        {
            if(dis[i]>ans2) ans2=dis[i];
        }
        printf("%d\n",ans2);
    }
    return 0;
}

