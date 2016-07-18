#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>

using namespace std;

int n,c,f,t;
int lnk[410];
int v[410];
int mat[410][410];
int ans;
string s[410][20];

bool find(int x)
{
    for(int i=1;i<=n;i++)
    {
        if(mat[x][i] && !v[i])
        {
            v[i]=1;
            if(lnk[i]==0 || find(lnk[i]))
            {
                lnk[i]=x;
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n >> c >> f;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=c;j++)
			{
	   			cin >> s[i][j];
			}
        memset(mat,0,sizeof(mat));
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
            {
                ans=0;
                for(int k=1;k<=c;k++)
                    for(int l=1;l<=c;l++)
                    {
                        if(s[i][k]==s[j][l])
                        {
                            ans++;
                            break;
                        }
                    }
                if(ans>f)
                {
                    mat[i][j]=1;
                    mat[j][i]=1;
                }
            }
        memset(lnk,0,sizeof(lnk));
        ans=0;
        for(int i=1;i<=n;i++)
        {
            memset(v,0,sizeof(v));
            if(find(i)) ans++;
        }
        if(ans==n) puts("not optimal"); else puts("optimal");
    }
    return 0;
}
