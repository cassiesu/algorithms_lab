#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

priority_queue<int> q;

int T,c,geld;
int mo[110];
int dp[110000];
int m;
int minh;
int z;
int r;

int main()
{
    cin >> T;
    while(T--)
    {
        cin >> c >> m;
        z=0;
        while(!q.empty()) q.pop();
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=c;i++)
        {
            cin >> mo[i];
            dp[mo[i]]=1;q.push(mo[i]);
        }
        while(!q.empty())
        {
            r=q.top();
            q.pop();
            for(int i=1;i<=c;i++)
            {
                if(r+mo[i]>10000) break;
                if(dp[r+mo[i]]==0 || dp[r]+1<dp[r+mo[i]])
                {
                    dp[r+mo[i]]=dp[r]+1;
                    q.push(r+mo[i]);
                }
            }
        }
        for(int i=1;i<=m;i++)
        {
            cin >> geld;
            if(dp[geld]>0) cout << dp[geld] << endl; else puts("not possible");
        }
    }
    return 0;
}
