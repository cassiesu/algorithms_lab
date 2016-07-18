#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;
using namespace CGAL;

// typedefs
typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef  K::Point_2 P;

const int MAXH = 200010;

double ceil_to_double(const K::FT &x)
{
    double a = ceil(to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return a;
}

int n;
double a, b;
P p[MAXH],tmp;
P ce;
K::FT t, ans, ori;
K::FT tp;

int main()
{
    ios::sync_with_stdio(false);
    while(cin >> n && n > 0)
    {
        for(int i=0;i<n;i++)
        {
            cin >> a >> b;
            p[i] = P(a,b);
        }
        Min_circle mc(p,p+n,true);
        Traits::Circle c = mc.circle();        
        ce = c.center();
        ori = c.squared_radius();
        ans = t = ori;
        Min_circle mc2(p,p+n-1,true);
        c = mc2.circle();
        ans = c.squared_radius();
        if(t>ans) t=ans;
        for(int i=0;i<n-1;i++)
        {
            tp = ori-squared_distance(ce,p[i]);
            if(tp<4)
            {
                tmp = p[i];p[i]=p[n-1];p[n-1]=tmp; 
                Min_circle mc(p,p+n-1,true);
                c = mc.circle();        
                ans = c.squared_radius();
                if(t>ans) t=ans;
                tmp = p[i];p[i]=p[n-1];p[n-1]=tmp; 
            }
        }
        cout << setiosflags(ios::fixed) << setprecision(0);
        cout << ceil_to_double(sqrt(t))<<endl;
    }
    return 0;
}
 
