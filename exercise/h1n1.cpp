#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>
#include <CGAL/Triangulation_face_base_with_info_2.h>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef Triangulation_data_structure_2<Vb,Fb> Tds;;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Delaunay;

Delaunay::Vertex_handle v, s;
Delaunay::Face_handle f;

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    int x,y;
    K::FT d;
    vector<K::Point_2> pts;//, pgs;
    pts.reserve(110010);
    //K::Point_2 p[110000];
    K::FT sum;
    bool flag;
    int k=0;

    while(cin >> n && n > 0) {
        // read points
        Delaunay t;
        t.clear();
        pts.clear();
        k+=10;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            K::Point_2 p(x,y);
            pts.push_back(p);
            //t.insert(p);
        }
        t.insert(pts.begin(),pts.end());
        cin >> m;
        for (int i = 0;i < m; ++i) {
            cin >> x >> y >> d;
            K::Point_2 p(x,y);
            f = t.locate(p);
            v = t.nearest_vertex(p,f);
            sum = squared_distance(v->point(),p);
            if(sum>=d)
            {
                vector<Delaunay::Face_handle> stk;
                stk.clear();
                f->info()=i+k;
                stk.push_back(f);
                flag = false;
                while(!stk.empty())
                {
                    f=stk.back();
                    stk.pop_back();
                    if(t.is_infinite(f)) {
                        flag = true;
                        break;
                    }
                    for(int j=0;j<3;j++) {
                        //cout << f->neighbor(j)->info() << " " <<  t.segment(Delaunay::Edge(f,j)).squared_length() << endl;
                        if (f->neighbor(j)->info()!=i+k && t.segment(Delaunay::Edge(f,j)).squared_length() >= 4 * d ) {
                            //cout << "here"<<endl;
                            f->neighbor(j)->info()=i+k;
                            stk.push_back(f->neighbor(j));
                        }
                    }
                }
                if(flag) cout <<"y"; else cout << "n";
            }
            else {
                cout << "n";
            }
        }
        cout << endl;
    }
    return 0;
}
