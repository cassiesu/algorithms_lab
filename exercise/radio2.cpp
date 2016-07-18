#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::Segment_2 S;

int n;
double X1,Y1,x2,y2;
Face_handle f;

double ceil_to_double(const K::FT &x) {
    double a = ceil(to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return a;
}

void testcase() {
    vector<P> pts;
    vector<P> pcs;
    P p;
    Vertex_handle v, vt;
    Face_handle f;
    K::FT ans, sum;
    K::FT px, py;
    S s[4];
    double x,y;
    bool flag;
    int fin, count;
    int m,n;

    cin >> m >> n;
    pts.reserve(m+1);
    pcs.reserve(n+1);
    pts.clear();
    pcs.clear();
    for(int i=0;i<m;i++) {
        cin >> x >> y;
        p=P(x,y);
        pts.push_back(p);
    }
    for(int i=0;i<n;i++) {
        cin >> x >> y;
        p=P(x,y);
        pcs.push_back(p);
    }
    Triangulation T, T2, T3;
    T.insert(pts.begin(),pts.end());
    T2.insert(pcs.begin(),pcs.end());
    fin=0;
    count=0;
    for (Face_iterator fit = T.finite_faces_begin(); fit !=T.finite_faces_end(); ++fit) {
        P op = T.dual(fit);
        sum=squared_distance(op,fit->vertex(1)->point());
        count=0;
        for(int i=0;i<n;i++) {
            ans = squared_distance(op,pcs[i]);
            if(ans<sum) {
                count++;
            }
        }
        if(count>fin) fin=count;
    }
    for (Edge_iterator eit = T.finite_edges_begin(); eit !=T.finite_edges_end(); ++eit) {
        double x1 = (T.segment(eit).source().x()+T.segment(eit).target().x())*1.0/2;
        double y1 = (T.segment(eit).source().y()+T.segment(eit).target().y())*1.0/2;
        sum=squared_distance(T.segment(eit).source(),T.segment(eit).target());
        P op=P(x1,y1);
        count=0;
        flag = 0;
        for(int i=0;i<m;i++) {
            ans = squared_distance(op,pts[i]);
            if(ans*4<sum) {
                flag = 1;
                break;
            }
        }
        if(!flag) {
            for(int i=0;i<n;i++) {
                ans = squared_distance(op,pcs[i]);
                if(ans*4<sum) {
                    count++;
                }
            }
            if(count>fin) fin=count;
        }
    } 
    */
    cout << count << endl;
}

int main() {
    int Z;
    cin >> Z;
    while(Z--) {
        testcase();
    }
    return 0;
}

