#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int INF = 1<<30;
const int DIVISOR = 1000000;
const int MAXH=500010;

int t,n,k;
long long dp[MAXH];
int A;

struct Pair
{
    int x;
    long long y;
    Pair(int a, long long b)
    {
        x = a;
        y = b;
    }
};

priority_queue<Pair> bst;

bool operator<(Pair a, Pair b)
{
    return a.y>b.y || (a.y==b.y && a.x > b.x);
}

int main()
{
    Pair tmp(0,0);

    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--)
    {
        cin >> n >> k;
        for(int i=1;i<=n;i++)
        {
            cin >> A;
            if(i==1) 
            {
                bst.push(Pair(1,0));
                dp[1]=0;
            }
            else 
            {
                while(1)
                {
                    tmp = bst.top();
                    if(i-tmp.x>k) bst.pop(); else break;
                }
                //cout << tmp.x << " " <<  tmp.y << endl;
                dp[i]=tmp.y+A;
                bst.push(Pair(i,dp[i]));
            }
        }
        while(!bst.empty()) bst.pop();
        cout << dp[n] << endl;
    }
    return 0;
}

