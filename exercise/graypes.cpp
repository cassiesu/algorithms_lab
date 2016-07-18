#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_iterator  Face_iterator;

Triangulation::Vertex_handle v, s;
Triangulation::Face_handle f;
double sum, ans;

int main()
{
    // read number of points
    ios::sync_with_stdio(false);
    int n, m;
    int x,y;
    vector<K::Point_2> pts;
    pts.reserve(110010);
    K::Point_2 p,q;

    while(cin >> n && n > 0)
    {
        // read points
        Triangulation t;
        pts.clear();
        for (int i = 0; i < n; ++i) 
        {
            cin >> x >> y;
            K::Point_2 p(x,y);
            pts.push_back(p);
            //t.insert(p);
        }
        t.insert(pts.begin(),pts.end());
        ans = 2000000000;
        for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
        {
            p=t.segment(e).source();
            q=t.segment(e).target();
            sum = to_double(squared_distance(p,q));
            if(sum < ans) ans = sum;
        }
        /*
        for(int i = 0; i < n; ++i)
        {
            f = t.finite_faces_begin();
            v = t.nearest_vertex(pts[i],f);
            t.remove(v);
            f = t.finite_faces_begin();
            v = t.nearest_vertex(pts[i],f);
            sum = to_double(squared_distance(v->point(),pts[i]));
            if(sum<ans) ans=sum;
            t.insert(pts[i]);
        }
        */
        ans = ceil(sqrt(ans) * 50);
        cout << setiosflags(ios::fixed);
        cout << setprecision(0);
        cout << ans << endl;
    }
    return 0;
}

