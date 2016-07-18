#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_iterator  Face_iterator;

Triangulation::Vertex_handle v, s;
Triangulation::Face_handle f;
K::FT sum;

int main()
{
    // read number of points
    ios::sync_with_stdio(false);
    int n, m;
    int x,y;
    vector<K::Point_2> pts;
    pts.reserve(110010);
    K::Point_2 p;

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
        }
        t.insert(pts.begin(),pts.end());
        cin >> m;
        for (int i = 0;i < m; ++i)
        {
            cin >> x >> y;
            K::Point_2 p(x,y);
            f = t.finite_faces_begin();
            v = t.nearest_vertex(p,f);
            sum = squared_distance(v->point(),p);
            cout << setiosflags(ios::fixed);
            cout << setprecision(0);
            cout << sum << endl;
        }
    }
    return 0;
}

