#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;
using namespace CGAL;

// typedefs
typedef  Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  Min_circle_2_traits_2<K>  Traits;
typedef  Min_circle_2<Traits>      Min_circle;
typedef K::Point_2 P;

const int MAXH = 200010;

int n;
double a, b;
P p[MAXH];
double t;
K::FT d;

double ceil_to_double(const K::FT&x)
{
    double a = ceil(to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return a;
}

int main()
{
    while(cin >> n && n > 0)
    {
        for(int i=0;i<n;i++)
        {
            cin >> a >> b;
            p[i] = P(a,b);
        }
        Min_circle mc(p,p+n,true);
        Traits::Circle c = mc.circle();        
        cout << setiosflags(ios::fixed) << setprecision(0);
        d = sqrt(c.squared_radius());
        t=to_double(d);
        cout << ceil_to_double(d) << endl;
    }
    return 0;
}
 
