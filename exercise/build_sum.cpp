#include<iostream>

using namespace std;

int T,n;
double a,d;

int main()
{
    cin >> T;
    while(T--)
    {
        cin >> n;
        d=0;
        for(int i=1;i<=n;i++)
        {
            cin >> a;
            d+=a;
        }
        cout << d << endl;
    }
}
