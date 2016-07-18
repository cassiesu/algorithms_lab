#include<iostream>

using namespace std;

int n;
int a;
int s,e;

int main()
{
    cin >> n;
    s=e=0;
    for(int i=1;i<=n;i++)
    {
        cin >> a;
        s+=a;
        s=s%2;
        if(s) e++;
    }
    cout << e*(e-1)/2+(n-e)*(n-e-1)/2 + (n-e) << endl;
    return 0;
}
