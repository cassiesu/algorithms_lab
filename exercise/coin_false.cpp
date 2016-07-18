#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define min(x,y) ((x<y)?(x):(y))
using namespace std;

int mat[250][250]; 
int dis[250];
int out[250];
int in[250];
int deg[250];
int q[2000],now,z;
int sum;
int s;
int n,m;
int a,b,c;
int ans,dd;
int dd2;
int t;
bool ff;

bool BFS()
{
    memset(dis,-1,sizeof(dis));
    dis[0]=0;
    now=0;z=1;
    q[1]=0;
    while (now<z)
    {
        now ++;
        for (int i=0;i<=n+1;i++)
           if (dis[i]<0 && mat[q[now]][i]>0)
           {
              dis[i]=dis[q[now]]+1; 
              z++;
              q[z]=i;
           }
    }
    if(dis[n+1]>0) return 1; else return 0;
}

int find(int x,int low)
{
    int a;

    if(x==n+1) return low;
    for (int i=0;i<=n+1;i++)
    {
        if (mat[x][i] > 0 && dis[i]==dis[x]+1)
        {
           a=find(i,min(low,mat[x][i])); 
           if(a>0)
           {
               mat[x][i]-=a;
               //mat[i][x]=-mat[x][i];
               mat[i][x]+=a;
               return a;
           }
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        memset(mat,0,sizeof(mat));
        memset(out,0,sizeof(out));
        memset(in,0,sizeof(in));
        memset(deg,0,sizeof(deg));
        for(int i=1;i<=m;i++)
        {
            scanf("%d %d %d",&a,&b,&c);
            if(a==b) continue;
            a++;
            b++;
            if(c==1)
            {
                mat[a][b]++;
                out[a]++;
                in[b]++;
            }
            if(c==2)
            {
                out[b]++;
                mat[b][a]++;
                in[a]++;
            }
            if(c==0)
            {
                deg[a]++;
                deg[b]++;
                mat[a][b]++;
                mat[b][a]++;
            }
        }
        ff=0;
        dd=dd2=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&s);
            if(s<out[i] || s-out[i]>deg[i])
            {
                ff=1;
            }
            mat[0][i]=s;//out flow;
            dd2+=s;
            mat[i][n+1]=in[i]+deg[i]+out[i]-s; // in flow;
            dd+=mat[i][n+1];
        }
        if(!ff)
        {
            ans=0;
            while (BFS())
            {
                while(1)
                {
                    sum = find(0,1000000000);
                    if (sum == 0) break;
                    ans+=sum;
                }
            }
        }
        if(ff || ans!=dd || dd!=dd2 || dd!=m) puts("no"); else puts("yes");
    }
    return 0;
}

