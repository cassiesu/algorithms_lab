#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdio>

using namespace std;

const int MAXM=15;
const int MAXH=110;

int n;
int t,e,s,a,b;
int E[MAXH][MAXH][MAXM];
int dis[MAXH][MAXH];
int d[MAXH];

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

void prim(int x,int y)
{
    int minh,minn;
    int clo[MAXH];
    int low[MAXH];
    bool v[MAXH];

    memset(v,0,sizeof(v));
    v[y]=1;
    for(int i=0;i<t;i++)
    {
        if(E[y][i][x]!=-1) low[i]=E[y][i][x]; else low[i]=1<<30;
        clo[i]=y;
    }
    for(int i=1;i<t;i++)
    {
        minh = 1 << 30;
        for(int j=0;j<t;j++)
        {
            if(!v[j] && minh > low[j])
            {
                minh=low[j];
                minn=j;
            }
        }
        low[minn]=0;
        v[minn]=1;
        for(int j=0;j<t;j++)
        {
            if(!v[j] && E[minn][j][x]!=-1 && E[minn][j][x] < low[j])
            {
                low[j]=E[minn][j][x];
                clo[j]=minn;
            }
        }
    }
    for(int i=0;i<t;i++)
    {
        if(i==y) continue;
        if(dis[clo[i]][i]==-1 || dis[clo[i]][i]>E[clo[i]][i][x]) dis[clo[i]][i]=E[clo[i]][i][x]; 
        if(dis[i][clo[i]]==-1 || dis[i][clo[i]]>E[clo[i]][i][x]) dis[i][clo[i]]=E[clo[i]][i][x]; 
    }
}

int search()
{
    int t1,t2;
    struct node tt(a,0);
    priority_queue<struct node> q;

    memset(d,-1,sizeof(d));
    d[a]=0;
    while(!q.empty()) q.pop();
    q.push(node(a,0));
    while(!q.empty())
    {
        tt=q.top();
        q.pop();
        t1=tt.num;
        for(int i=0;i<t;i++)
        {
            if(dis[t1][i]>=0 && (d[i]==-1 || d[t1]+dis[t1][i] < d[i]))
            {
                d[i]=d[t1]+dis[t1][i];
                q.push(node(i,d[i]));
            }
        }
    }
    return d[b];
}

int main()
{
    int homeland;
    int t1,t2;

    cin >> n;
    while(n--)
    {
        cin >> t >> e >> s >> a >> b;
        memset(E,-1,sizeof(E));
        for(int i=1;i<=e;i++)
        {
            cin >> t1 >> t2;
            for(int j=1;j<=s;j++)
            {
                cin >> E[t1][t2][j];
                E[t2][t1][j]=E[t1][t2][j];
            }
        }
        for(int i=0;i<t;i++)
            for(int j=0;j<t;j++)
                dis[i][j]=-1;
        for(int i=1;i<=s;i++)
        {
            cin >> homeland;
            prim(i,homeland);
        }
        cout << search() << endl;
    }
    return 0;
}

