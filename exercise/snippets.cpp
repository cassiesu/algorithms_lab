#include<iostream>
#include<queue>

using namespace std;

int t;
int n;
int m[2100];
int p[66000];
int a[2100];
int b[2100];
int sum[2100];
int ans;
struct node1
{
    int x;
    int y;
    /*
    node1(int a, int b)
    {
        x=a;
        y=b;
    }
    */
};

struct node2
{
    int x;
    int y;
    /*
    node2(int a, int b)
    {
        x=a;
        y=b;
    }
    */
};

node1 minh,tmp1;
node2 maxh,tmp2;
priority_queue<node1> q1;
priority_queue<node2> q2;

bool operator<(const node1 &a, const node1 &b)
{
    return a.x>b.x;
}

bool operator<(const node2 &a, const node2 &b)
{
    return a.x<b.x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> t;
    while(t--)
    {
        cin >> n;
        sum[0]=0;
        for(int i=1;i<=n;i++)
        {
            cin >> m[i];
            sum[i]=sum[i-1]+m[i];
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m[i];j++)
            {
                cin >> p[sum[i-1]+j];
            }
        }
        for(int i=1;i<=n;i++)
        {
            a[i]=1;
            b[i]=p[sum[i-1]+a[i]];
            tmp1.x=b[i];tmp1.y=i;
            tmp2.x=b[i];tmp2.y=i;
            q1.push(tmp1);
            q2.push(tmp2);
        }
        ans=2000000000;
        while(1)
        {
            minh=q1.top();
            q1.pop();
            maxh=q2.top();
            //q2.pop();
            //cout << minh.x << " " << maxh.x<<endl;
            if(maxh.x-minh.x+1<=ans) ans=maxh.x-minh.x+1;
            a[minh.y]++;
            if(a[minh.y]>m[minh.y]) break;
            b[minh.y]=p[sum[minh.y-1]+a[minh.y]];
            tmp1.x=b[minh.y];tmp1.y=minh.y;
            tmp2.x=b[minh.y];tmp2.y=minh.y;
            q1.push(tmp1);
            q2.push(tmp2);
        }
        while(!q1.empty()) q1.pop();
        while(!q2.empty()) q2.pop();
        cout << ans << endl;
    }
    return 0;
}

