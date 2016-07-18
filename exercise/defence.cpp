#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define min(x,y) ((x<y)?(x):(y))
using namespace std;

int mat[550][550]; 
int dis[550];
int q[5000],now,z;
int ans1,ans2,sum;
int tmp;
int n;
int total,total_;
int lft[550];
int l,p,a,b,c,d;
int g;

inline int minh(int x, int y)
{
    return x<y?x:y;
}

void init()
{
    cin >> l >> p;
    memset(lft,0,sizeof(lft));
    total=total_=0;
    for(int i=1;i<=l;i++)
    {
        cin >> g >> d;
        if(g-d>0)
        {
            mat[l+2][i]=g-d;
        }
        else
        {
            mat[i][l+3]=d-g;
            total+=d-g;
        }
    }
    for(int i=0;i<p;i++)
    {
        cin >> a >> b >> c >> d;
        if(a==b) continue;
        a++;b++;
        lft[a]-=c;
        lft[b]+=c;
        mat[a][b]=d-c;
    }
    for(int i=1;i<=l;i++)
    {
        if(lft[i]>0)
        {
            total_+=lft[i];
            mat[0][i]=lft[i];
        }
        else
        {
            mat[i][l+1]=-lft[i];
        }
    }
    mat[l+2][0]=1000000000;
    mat[l+1][l+3]=1000000000;
}

bool BFS(int x,int y)
{
    memset(dis,-1,sizeof(dis));
    dis[x]=0;
    now=0;z=1;
    q[1]=x;
    while (now<z)
    {
        now ++;
        for (int i=0;i<=l+3;i++)
           if (dis[i]<0 && mat[q[now]][i]>0)
           {
              dis[i]=dis[q[now]]+1; 
              z++;
              q[z]=i;
           }
    }
    if (dis[y]>0) return 1; else return 0;
}

int find(int x,int y, int low)
{
    int a;

    if (x==y)return low; 
    for (int i=0;i<=l+3;i++)
    {
        if (mat[x][i] >0 && dis[i]==dis[x]+1)
        {
           a=find(i,y,min(low,mat[x][i])); 
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
    ios_base::sync_with_stdio(false);
    cin >> n;
    while(n--)
    {
        memset(mat,0,sizeof(mat));
        init();
        ans1=0;
        while (BFS(l+2,l+3))
        {
            while(1)
            {
                sum = find(l+2,l+3,1000000000);
                if (sum == 0) break;
                ans1+=sum;
            }
        }
/*        ans2=0;
        while (BFS(0,l+1))
        {
            while(1)
            {
                sum = find(0,l+1,1000000000);
                if (sum == 0) break;
                ans2+=sum;
            }
        }
        */
        if(ans1==total+total_) puts("yes"); else puts("no");
    }
    return 0;
}

