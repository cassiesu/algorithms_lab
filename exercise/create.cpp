#include<iostream>
#include<cstdlib>

using namespace std;

int main()
{
    int N,T;
    int l,p;

    N = 1;
    cout << N << endl;
    while(N--)
    {
        T = rand()%100;
        cout << T << endl;
        for(int i=1;i<=T;i++)
        {
            l = rand()%1000;
            p = rand()%1000;
            cout << l << " " << p << endl;
        }
    }
    return 0;
}
