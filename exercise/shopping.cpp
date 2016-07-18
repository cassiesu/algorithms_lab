#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define min(x,y) ((x<y)?(x):(y))
using namespace std;

int mat[550][550]; 
int dis[550];
int q[5000],now,z;
int ans,sum;
int tmp;
int n;
int l,p,a,b,c,d;
int g;
int m,s;

inline int minh(int x, int y)
{
    return x<y?x:y;
}

void init()
{
    int tmp;
    cin >> n >> m >> s;
    for(int i=0;i<s;i++)
    {
        cin >> tmp;
        mat[tmp][n] = 1;
    }
    for(int i=0;i<m;i++)
    {
        cin >> a >> b;
        mat[a][b]=1;
        mat[b][a]=1;
    }
}

bool BFS()
{
    memset(dis,-1,sizeof(dis));
    dis[0]=0;
    now=0;z=1;
    q[1]=0;
    while (now<z)
    {
        now ++;
        for (int i=0;i<=n;i++)
           if (dis[i]<0 && mat[q[now]][i]>0)
           {
              dis[i]=dis[q[now]]+1; 
              z++;
              q[z]=i;
           }
    }
    if (dis[n]>0) return 1; else return 0;
}

int find(int x, int low)
{
    int a;

    if (x==n)return low; 
    for (int i=0;i<=n;i++)
    {
        if (mat[x][i] >0 && dis[i]==dis[x]+1)
        {
           a=find(i,min(low,mat[x][i])); 
           if(a>0)
           {
               mat[x][i]-=a;
               mat[i][x]+=a;
               return a;
           }
        }
    }
    return 0;
}

int main()
{
    int T;
    ios_base::sync_with_stdio(false);
    cin >> T;
    while(T--)
    {
        memset(mat,0,sizeof(mat));
        init();
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
        if(ans>=s) puts("yes"); else puts("no");
    }
    return 0;
}

