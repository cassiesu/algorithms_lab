#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

struct Boat
{
    int l,p;
};

struct Boat boat[100010];

int T,N;
int ans;
int i;
int maxp;
int tmp,tmp2;
int ml;

bool operator<(struct Boat x, struct Boat y)
{
    return x.p<y.p || (x.p==y.p && x.l<y.l);
}

int main()
{
    cin >> T;
    while(T--)
    {
        cin >> N;
        for(i = 1;i <= N;i++)
        {
            cin >> boat[i].l >> boat[i].p;
        }
        sort(boat+1,boat+1+N);
        maxp=boat[1].p;
        ml=boat[1].l;
        ans=1;
        for(i=2;i<=N;i++)
        {
            if(boat[i].p<maxp) 
            {
                tmp=maxp-ml;
                if(boat[i].p>=tmp)
                {
                    if(boat[i].p>tmp+boat[i].l) tmp2=boat[i].p; else tmp2=tmp+boat[i].l;
                    if(tmp2<maxp)
                    {
                        maxp=tmp2;
                        ml=boat[i].l;
                    }
                }
            }
            else
            {
                ans++;
                if(boat[i].p>maxp+boat[i].l) maxp=boat[i].p; else maxp=maxp+boat[i].l;
                ml=boat[i].l;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

