#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_iterator  Face_iterator;

//Triangulation::Vertex_handle v, s;
Triangulation::Face_handle f;
double sum;
int ans;
bool v[1100000];

map<K::Point_2,int> mmap;

int main()
{
    // read number of points
    ios::sync_with_stdio(false);
    int n, d;
    int x,y;
    int t;
    int t1;
    vector<K::Point_2> pts;
    pts.reserve(1100100);
    K::Point_2 p,q;

    cin >> t;
    while(t--)
    {
        cin >> n>>d;
        // read points
        Triangulation t;
        pts.clear();
        mmap.clear();
        for (int i = 0; i < n; ++i) 
        {
            cin >> x >> y;
            K::Point_2 p(x,y);
            pts.push_back(p);
            mmap.insert(pair<K::Point_2,int>(p,i));
            //t.insert(p);
        }
        t.insert(pts.begin(),pts.end());
        memset(v,0,sizeof(v));
        for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
        {
            p=t.segment(e).source();
            q=t.segment(e).target();
            sum = sqrt(to_double(squared_distance(p,q)));
            if(sum < d) 
            {
                t1 = mmap.find(p)->second;
                if(!v[t1]) v[t1]=1;
                t1 = mmap.find(q)->second;
                if(!v[t1]) v[t1]=1;
            }
        }
        ans=0;
        for(int i=0;i<n;i++)
        {
            if(v[i]) ans++;
        }
        cout << setiosflags(ios::fixed);
        cout << setprecision(0);
        cout << ans << endl;
    }
    return 0;
}

