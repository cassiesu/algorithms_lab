#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int MAXM= 1000010;
const int MAXH= 1010;

int t,n,m,ans;
int a,b;

struct bridge
{
    int a,b;
    bool operator<(const bridge x) const
    {
        return x.a>a || (x.a==a && x.b>b);
    }
};

struct bridge node[MAXM];
int num[MAXH];
int dfs[MAXH];
int low[MAXH];
int mat[MAXH][MAXH];
int dfsnum;


void search(int x,int fx)
{
    int t;
    int t2;

    dfsnum++;
    dfs[x]=low[x]=dfsnum;
    for(int i=1;i<=num[x];i++)
    {
        t=mat[x][i];
        if(t==fx) continue;
        if(dfs[t]==0)
        {
            search(t,x);
            if(low[t]<low[x]) low[x]=low[t];
            if(dfs[x]<low[t])
            {
                ans++;
                node[ans].a=x;
                node[ans].b=t;
                if(node[ans].a>node[ans].b)
                {
                    t2=node[ans].a;
                    node[ans].a=node[ans].b;
                    node[ans].b=t2;
                }
            }
        }
        else
        {
            if(low[x]>low[t]) low[x]=low[t];
        }
    }
}

int main()
{
    int tt;

    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        memset(num,0,sizeof(num));
        memset(mat,0,sizeof(mat));
        for(int i=1;i<=m;i++)
        {
            cin >> a >> b;
            num[a]++;
            num[b]++;
            mat[a][num[a]]=b;
            mat[b][num[b]]=a;
        }
        memset(dfs,0,sizeof(dfs));
        memset(low,0,sizeof(low));
        dfsnum=0;
        ans=0;
        search(a,-1);
        if(ans>0) sort(node+1,node+ans+1);
        cout << ans << endl;
        for(int i=1;i<=ans;i++)
        {
            cout << node[i].a << " " << node[i].b << endl;
        }
    }
    return 0;
}

