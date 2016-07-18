#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel K;

double floor_to_double(const K::FT& x)
{
  double a = floor(to_double(x));
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
K::FT tx,ty,ansx,ansy;
K::FT dis, sum;
bool flag;

int main()
{
    int n;
    double x,y,a,b,c,d;

    ios::sync_with_stdio(false);
    while(cin >> n && n>0)
    {
        ff=0;
        cin >> x >> y >> a >> b;
        p = P(x,y);q = P(a,b);
        r = R(p,q);
        dis = exp(log(2)*53);
        flag = 0;
        for(int i=1;i<=n;i++)
        {
            cin >> c >> d >> a >> b;
            t1 = P(c,d);t2 = P(a,b);
            s = S(t1,t2);
            ff = do_intersect(r,s);
            if(ff)
            {
                Object o = intersection(r,s);
                if(const P* op = object_cast<P>(&o))
                {
                    tx = op->x();
                    ty = op->y();
                    sum = (tx-x)*(tx-x)+(ty-y)*(ty-y);
                    if(sum<dis || flag == 0)
                    {
                        flag = 1;
                        dis = sum;
                        ansx = tx;
                        ansy = ty;
                    }
                }
                else
                {
                    if (const S* os = object_cast<S>(&o))
                    {
                        tx = os->source().x();
                        ty = os->source().y();
                        sum = (tx-x)*(tx-x)+(ty-y)*(ty-y);
                        if(sum<dis || flag == 0)
                        {
                            flag = 1;
                            dis = sum;
                            ansx = tx;
                            ansy = ty;
                        }
                        tx = os->target().x();
                        ty = os->target().y();
                        sum = (tx-x)*(tx-x)+(ty-y)*(ty-y);
                        if(sum<dis || flag == 0) 
                        {
                            flag = 1;
                            dis = sum;
                            ansx = tx;
                            ansy = ty;
                        }
                    }
                }
            }
        }
        cout << setiosflags(ios::fixed);
        cout << setprecision(0);
        if(flag) cout << floor_to_double(ansx) << " " << floor_to_double(ansy) << endl;
        else cout << "no" << endl;
    }
    return 0;
}


