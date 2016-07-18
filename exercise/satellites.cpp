#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int lnk[110];
int pnt[110];
bool v[110];
bool matg[110];
bool mats[110];
bool mat[110][110];
int ansg,anss;
int ag,as;
int g,s,l,a,b;
int t;

bool find(int x)
{
    for(int i=1;i<=s;i++)
    {
        if(mat[x][i] && !v[i])
        {
            v[i]=1;
            if(lnk[i]==0 || find(lnk[i]))
            {
                lnk[i]=x;
                pnt[x]=i;
                return 1;
            }
        }
    }
    return 0;
}

bool find2(int x)
{
    for(int i=1;i<=g;i++)
    {
        if(!matg[i] && mat[i][x])
        {
            matg[i]=1;
            mats[pnt[i]]=1;
            find2(pnt[i]);
        }
    }
}

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> g >> s >> l;
        memset(mat,0,sizeof(mat));
        for(int i=1;i<=l;i++)
        {
            cin >> a >> b;
            mat[a+1][b+1]=1;
        }
        memset(lnk,0,sizeof(lnk));
        memset(pnt,0,sizeof(pnt));
        memset(matg,0,sizeof(matg));
        memset(mats,0,sizeof(mats));
        for(int i=1;i<=g;i++)
        {
            memset(v,0,sizeof(v));
            find(i);
        }
        for(int i=1;i<=s;i++)
        {
            if(lnk[i]==0)
            {
                mats[i]=1;
                find2(i);
            }
        }
        ansg=anss=0;
        for(int i=1;i<=g;i++)
        {
            if(matg[i])
            {
                ansg++;
            }
        }
        for(int i=1;i<=s;i++)
        {
            if(!mats[i])
            {
                anss++;
            }
        }
        cout << ansg << " " << anss << endl;
        ag=as=0;
        for(int i=1;i<=g;i++)
        {
            if(matg[i])
            {
                ag++;
                if(anss==0 && ag==ansg) cout << i-1 << endl; else cout << i-1 << " ";
            }
        }
        for(int i=1;i<=s;i++)
        {
            if(!mats[i])
            {
                as++;
                if (as<anss) cout << i-1 << " "; else cout << i-1 << endl;
            }
        }
    }
    return 0;
}

