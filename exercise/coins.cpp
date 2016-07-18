#include<iostream>

using namespace std;

const int MAXH=1010;

int dp[2][MAXH][MAXH];
int sum[MAXH];
int c,n,t;

int main()
{
    cin >> c;
    while(c--)
    {
        cin >> n;
        sum[0]=0;
        for(int i=1;i<=n;i++)
        {
            cin >> dp[1][i][i];
            dp[0][i][i]=0;
            sum[i]=sum[i-1]+dp[1][i][i];
        }
        for(int i=2;i<=n;i++)
            for(int j=1;j+i-1<=n;j++)
            {
                dp[i%2][j][j+i-1]=dp[i%2][j][j+i-2]+dp[1][j+i-1][j+i-1];
                t=dp[i%2][j+1][j+i-1]+dp[1][j][j];
                if(t>dp[i%2][j][j+i-1]) dp[i%2][j][j+i-1]=t;
                dp[(i+1)%2][j][j+i-1]=sum[j+i-1]-sum[j-1]-dp[i%2][j][j+i-1];
            }
        cout << dp[n%2][1][n] << endl;
        // dp[i,j]=dp[i+1,j]+w[i],dp[i,j-1]+w[j]
    }
    return 0;
}

//3 1 2
//1 4 9 4
//
