#include<cstdio>
#include<iostream>

using namespace std;

int T;
long N,maxh,ans;
int h;

int main()
{
    std :: ios_base :: sync_with_stdio(false);
    scanf("%d",&T);
    while(T--)
    {
        maxh=ans=0;
        scanf("%ld",&N);
        if(N==0) 
        {
            puts("0");
            continue;
        }
        scanf("%ld",&h);
        maxh=h;
        ans++;
        for(int i=2;i<=N;i++)
        {
            maxh--;
            ans++;
            scanf("%ld",&h);
            if(maxh<h) maxh=h;
            if(maxh==1) 
            {
                i++;
                for(;i<=N;i++)
                    scanf("%ld",&h);
                break;
            }
        }
        printf("%ld\n",ans);
    }
    return 0;
}
