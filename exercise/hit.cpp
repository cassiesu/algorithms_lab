#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/intersections.h>
#include <iostream>
#include <cmath>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

const int MAXH = 20010;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

P p,q,t1,t2;
R r;
S s;
bool ff;

int main()
{
    double n,x,y,a,b;

    while(cin >> n && n>0)
    {
        ff=0;
        cin >> x >> y >> a >> b;
        p = P(x,y);q = P(a,b);
        r = R(p,q);
        for(int i=1;i<=n;i++)
        {
            cin >> x >> y >> a >> b;
            t1 = P(x,y);t2 = P(a,b);
            s = S(t1,t2);
            if(!ff) ff = CGAL::do_intersect(r,s);
        }
        if(ff) puts("yes"); else puts("no");
    }
    return 0;
}


