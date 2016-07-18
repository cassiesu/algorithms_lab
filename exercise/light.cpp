#include<iostream>

using namespace std;

const int MAXH = 100010;

int light[MAXH][2];
bool bit[MAXH];
int ans[2];
int n,k,x,t;
bool check[20];
int tmp1;
int sum;

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n >> k >> x;
        for(int i=0;i<n;i++)
        {
            cin >> bit[i];
        }
        for(int i=k-1;i>=0;i--)
        {
            check[i]=x%2;
            x/=2;
        }
        for(int i=n/k-1;i>=0;i--)
        {
            sum=0;
            for(int j=0;j<=k-1;j++)
            {
                if(bit[i*k+j]==check[j]) sum++;
            }
            light[i][1]=k-sum;
            light[i][0]=sum;
        }
        ans[1]=light[0][1];
        ans[0]=light[0][0];

        for(int i=1;i<n/k;i++)
        {
            tmp1=ans[1]+light[i][1];
            if(light[i][1]+1+ans[0]<tmp1) tmp1=ans[0]+1+light[i][1];
            ans[0]+=light[i][0];
            if(light[i][0]+1+ans[1]<ans[0]) ans[0]=ans[1]+1+light[i][0];
            ans[1]=tmp1;
        }
        if(ans[0]+1>ans[1]) cout << ans[1] << endl; else cout << ans[0]+1<<endl;
    }
    return 0;
}
