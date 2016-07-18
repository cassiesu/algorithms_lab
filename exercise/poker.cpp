#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int stack[6];
int sum[6];
int sum2[6];
int pos[6];
int n;
int dp[100000000];
int mat[1100000];
int ans;
int state[6];
int num;
int tmp;
int mi,mj;

void search(int x) {
    bool flag;
    int tmp2;

    if(x==n) {
        if(tmp==0) return;
        if(tmp>=2) tmp2 = 1<<(tmp-2); else tmp2 = 0;
        if(dp[mi]+tmp2>dp[mj]) {
            /*
            for(int i=0;i<n;i++)
                cout << pos[i]<<" ";
            cout << endl;
            for(int i=0;i<n;i++)
                cout << state[i]<<" ";
            cout << endl;
            */
            dp[mj]=dp[mi]+tmp2;
            if(dp[mj] > ans) ans = dp[mj];
        }
    }
    else {
        for(int i=stack[x]-1;i>=-1;i--) {
            pos[x]=i;
            if(i==-1) {
                state[x]=0;
                mi+=(pos[x]+1)*sum[x+1];
                mj+=(pos[x]+1)*sum[x+1];
                search(x+1);
                mi-=(pos[x]+1)*sum[x+1];
                mj-=(pos[x]+1)*sum[x+1];
            }
            else
            {
                for(int j=0;j<=1;j++) {
                    state[x]=j;
                    if(j==1) {
                        flag = 0;
                        for(int k=0;k<x;k++)
                            if(state[k]==1 && mat[sum2[x]+i]!=mat[sum2[k]+pos[k]]) {
                                flag = 1;
                                break;
                            }
                        if(flag) continue;
                    }
                    if(j==1) tmp++;
                    mi+=(pos[x]+1)*sum[x+1];
                    mj+=(pos[x]-state[x]+1)*sum[x+1];
                    search(x+1);
                    mi-=(pos[x]+1)*sum[x+1];
                    mj-=(pos[x]-state[x]+1)*sum[x+1];
                    if(j==1) tmp--;
                }
            }
        }
    }
}

void testcase() {

    cin >> n;
    memset(stack,0,sizeof(stack));
    memset(mat,0,sizeof(mat));
    memset(sum2,0,sizeof(sum2));
    memset(sum,0,sizeof(sum));
    sum2[0]=0;
    for(int i=0;i<n;i++) {
        cin >> stack[i];
        sum2[i+1]=sum2[i]+stack[i];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<stack[i];j++) {
            cin >> mat[j+sum2[i]];
        }
    }
    sum[n]=1;
    for(int i=n-1;i>=0;i--)
        sum[i]=sum[i+1]*(stack[i]+2);
    memset(dp,0,sizeof(dp));
    ans = 0;
    tmp = 0;
    mi = mj = 0;
    search(0);
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int Z;
    cin >> Z;
    while(Z--) {
        testcase();
    }
    return 0;
}

