#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace CGAL;

typedef  CGAL::Exact_predicates_exact_constructions_kernel K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef  K::Point_2 P;

double ceil_to_double(const K::FT &x)
{
    double a = ceil(to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return a;
}

int n;
int a,b;
int ya,yb;
K::FT t, ans, ori, sum;
vector<P> po;
int T;
P yp;
int k;

bool comp(P x, P y)
{
    return squared_distance(x,yp)<squared_distance(y,yp);
}

int main() {

    ios::sync_with_stdio(false);
    po.reserve(34010);
    cin >> T;
    while(T--) {
        cin >> n;
        po.clear();
        cin >> ya >> yb;
        yp = P(ya,yb);
        for(int i=1;i<n;i++) {
            cin >> a >> b;
            P p(a,b);
            po.push_back(p);
        }
        sort(po.begin(),po.end(),comp);
        k=n-1;
        Min_circle mc(po.begin()+k-1,po.end(),true);
        if(k==1) ans = 0; else ans = squared_distance(po[k-2],yp);
        for(int i=k-2;i>=0;i--) {
            if(i==0) sum = 0; else sum = squared_distance(po[i-1],yp);
            mc.insert(po[i]);
            Traits::Circle c = mc.circle();        
            ori = c.squared_radius();
            if(sum>ori) {
                if(sum<ans) ans = sum;
            }
            else {
                if(ori<ans) ans = ori;
                break;
            }
        }
        cout << setiosflags(ios::fixed) << setprecision(0);
        cout << ceil_to_double(ans) <<endl;
    }
    return 0;
}
 
