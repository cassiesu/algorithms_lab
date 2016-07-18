#include<iostream>

using namespace std;

char indicator;

bool ff;
int lft, rgt;
int ans, ansk;
int M,N,K;
int Nr[110];
int scales[110][110];
int ind[110];
int tmp;

int main()
{
    cin >> M;
    while(M--)
    {
        cin >> N >> K;
        for(int i=1;i<=K;i++)
        {
            cin >> Nr[i];
            for(int j=1;j<=2*Nr[i];j++)
            {
                cin >> scales[i][j];
            }
            cin >> indicator;
            while(indicator!='<' && indicator!='>' && indicator!='=') cin >> indicator;
            if (indicator=='<') ind[i]=-1;
            if (indicator=='=') ind[i]=0;
            if (indicator=='>') ind[i]=+1;
        }
        ans=ansk=0;
        for(int i=1;i<=N;i++)
        {
            tmp=-1;
            ff=1;
            for(int j=1;j<=K;j++)
            {
                lft=rgt=0;
                for(int k=1;k<=Nr[j];k++)
                {
                    if(scales[j][k]==i) lft+=tmp;
                    if(scales[j][k+Nr[j]]==i) rgt+=tmp;
                }
                if(lft-rgt!=ind[j])
                {
                    ff=0;
                    break;
                }
            }
            if(ff)
            {
                ans++;
                ansk=i;
                continue;
            }
            tmp=1;
            ff=1;
            for(int j=1;j<=K;j++)
            {
                lft=rgt=0;
                for(int k=1;k<=Nr[j];k++)
                {
                    if(scales[j][k]==i) lft+=tmp;
                    if(scales[j][k+Nr[j]]==i) rgt+=tmp;
                }
                if(lft-rgt!=ind[j]) 
                {
                    ff=0;
                    break;
                }
            }
            if(ff)
            {
                ans++;
                ansk=i;
            }
        }
        if(ans==1)
        {
            cout << ansk << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
    return 0;
}
