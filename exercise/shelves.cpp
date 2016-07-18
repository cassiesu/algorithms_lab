#include<iostream>

long long T, p, q;
long long l, m, n;
long long ans, ansk;
long long x, tmp;

using namespace std;

long long gcd(long long x, long long y)
{
    if(x % y == 0) return y; else return gcd(y, x % y);
}

int main()
{
    cin >> T;
    while( T-- )
    {
        cin >> l >> m >> n;
        ans = l % n % m;
        ansk = l /n;
        p = l / n;
        tmp = m * n / gcd(m, n);
        for(long long i = 1;i <= tmp;i ++)
        {
           p--;
           if (p < 0) break;
           q = (l - p * n) % m;
           if(q < ans)
           {
               ans = q;
               ansk = p;
           }
        }
        cout <<  (l - ans - ansk * n) / m << " " << ansk << " " << ans << endl;
    }
    return 0;
}
