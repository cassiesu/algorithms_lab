#include<iostream>
#include<cstring>

using namespace std;

struct Tree
{
    int to,next;
};

struct Tree point[200100];
bool v[100100];
int edge[100100];
int ans;
int s, t;
int n;
int a,b;

void search(int x, int step)
{
    int tmp, tmp2;
    
    v[x]=1;
    if(step>ans)
    {
        s = x;
        ans = step;
    }
    tmp = edge[x];
    while(tmp!=0)
    {
        tmp2=point[tmp].to;
        if(!v[tmp2]) search(tmp2,step+1); 
        tmp = point[tmp].next;
    }
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n;
        memset(edge,0,sizeof(edge));
        memset(point,0,sizeof(point));
        for(int i=1;i<n;i++)
        {
            cin >> a >> b;
            point[2*i-1].to = b;
            point[2*i-1].next = edge[a];
            edge[a]=2*i-1;
            point[2*i].to = a;
            point[2*i].next = edge[b];
            edge[b]=2*i;
        }
        memset(v,0,sizeof(v));
        ans = 0 ;
        search(0, 0);
        memset(v,0,sizeof(v));
        ans = 0;
        search(s, 0); 
        cout << ans + 1 << endl;

    }
    return 0;
}

