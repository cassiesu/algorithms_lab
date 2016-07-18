#include<iostream>
#include<cstring>

using namespace std;

int optimal;
int N,X,Y,Sx,Sy,Fx,Fy,P;
bool v[40][40][10][10];
int step[40][40];
int O1x,O1y,O2x,O2y;
//int ve[40][40][3];
int now,z;
int a[500000][10];

inline bool check_sp(int x, int y)
{
    if(x<=3 && x>=-3 && y<=3 && y>=-3) return 1; else return 0;
}

inline bool check_ch(int x, int y)
{
    if(x<X && x>=0 && y<Y && y>=0) return 1; else return 0;
}

int search()
{
    int x; int y; int vx; int vy; int stp;
    int tx,ty;
    while(now <= z)
    {
        x=a[now%400000+1][1];y=a[now%400000+1][2];vx=a[now%400000+1][3];vy=a[now%400000+1][4];stp=a[now%400000+1][5];
        step[x][y]=stp;
        if(x==Fx && y==Fy) return stp;
        for(int i=-1;i<=1;i++)
            for(int j=-1;j<=1;j++)
            {
                tx=x+vx+i;ty=y+vy+j;
                if(check_sp(vx+i,vy+j) && check_ch(tx,ty) && !v[tx][ty][i+vx+4][j+vy+4])
                {
                    z++;
                    a[z%400000+1][1]=tx;a[z%400000+1][2]=ty;a[z%400000+1][3]=vx+i;a[z%400000+1][4]=vy+j;a[z%400000+1][5]=stp+1;
                    v[tx][ty][i+vx+4][j+vy+4]=1;
                }
            }
        now++;
    }
    return -1;
}

int main()
{
    int j1,k1;

    cin >> N;
    while(N--)
    {
        cin >> X >> Y;
        cin >> Sx >> Sy >> Fx >> Fy;
        cin >> P;
        memset(v,0,sizeof(v));
        for(int i=1;i<=P;i++)
        {
            cin >> O1x >> O1y >> O2x >> O2y;
            for(int j=O1x;j<=O2x;j++)
                for(int k=O1y;k<=O2y;k++)
                    for(int j1=1;j1<=7;j1++)
                        for(int k1=1;k1<=7;k1++)
                        {
                            v[j][k][j1][k1]=1;
                        }
        }
        memset(step,-1,sizeof(step));
        now=z=1;
        //for(int j1=1;j1<=7;j1++)
        //    for(int k1=1;k1<=7;k1++)
        j1=4;k1=4;
            {
                a[z+1][1]=Sx;a[z+1][2]=Sy;a[z+1][3]=j1-4;a[z+1][4]=k1-4;a[z+1][5]=0;
                v[Sx][Sy][j1][k1]=1;
            }
        optimal = -1;
        if(!v[Fx][Fy][1][1])  optimal = search();
        if(optimal != -1) cout << "Optimal solution takes " << optimal << " hops.\n";
        else cout << "No solution.\n";
    }
    return 0;
}

