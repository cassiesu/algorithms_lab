#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

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

double ceil_to_double(const K::FT &x) {
    double a = ceil(to_double(x));
    while(a<x) a++;
    while(a-1>=x) a--;
    return a;
}

void testcase() {
    vector<P> pts;
    P p;
    Vertex_handle v, vt;
    Face_handle f;
    K::FT ans, sum;
    K::FT px, py;
    S s[4];
    double x,y;

    cin >> X1 >> Y1 >> x2 >> y2;
    s[0]=S(P(X1,Y1),P(X1,y2));
    s[1]=S(P(x2,Y1),P(x2,y2));
    s[2]=S(P(X1,Y1),P(x2,Y1));
    s[3]=S(P(X1,y2),P(x2,y2));
    pts.reserve(n+1);
    pts.clear();
    Triangulation T;
    for(int i=0;i<n;i++) {
        cin >> x >> y;
        p=P(x,y);
        pts.push_back(p);
    }
    T.insert(pts.begin(),pts.end());
    sum=0;
    for (Face_iterator fit = T.finite_faces_begin(); fit !=T.finite_faces_end(); ++fit) {
        P op = T.dual(fit);
        px=op.x();
        py=op.y();
        v = fit->vertex(1);
        S stemp = S(op,v->point());
        if(px>=X1 && px<=x2 && py>=Y1 && py<=y2) {
            ans = squared_distance(op,v->point());
            if(ans>sum) sum=ans;
        }
    }
    f=T.finite_faces_begin();
    v=T.nearest_vertex(P(X1,Y1),f);
    ans = squared_distance(P(X1,Y1),v->point());
    if(ans>sum) sum=ans;
    f=T.finite_faces_begin();
    v=T.nearest_vertex(P(X1,y2),f);
    ans = squared_distance(P(X1,y2),v->point());
    if(ans>sum) sum=ans;
    f=T.finite_faces_begin();
    v=T.nearest_vertex(P(x2,Y1),f);
    ans = squared_distance(P(x2,Y1),v->point());
    if(ans>sum) sum=ans;
    f=T.finite_faces_begin();
    v=T.nearest_vertex(P(x2,y2),f);
    ans = squared_distance(P(x2,y2),v->point());
    if(ans>sum) sum=ans;
    for (Edge_iterator eit = T.finite_edges_begin(); eit !=T.finite_edges_end();++eit) {
        CGAL::Object o = T.dual(eit);
        v = eit->first->vertex((eit->second+1)%3);
        if (const R* rr=CGAL::object_cast<R>(&o)) {
            for(int j=0;j<4;j++) {
                if(do_intersect(*rr,s[j])) {
                    Object o2 = intersection(*rr,s[j]);
                    if(const P* pp=object_cast<P>(&o2)) {
                        ans = squared_distance(*pp,v->point());
                        if(ans>sum) sum=ans;
                    }
                }
            }
        }
        if (const S* ss=CGAL::object_cast<S>(&o)) {
            for(int j=0;j<4;j++) {
                if(do_intersect(*ss,s[j])) {
                    Object o2 = intersection(*ss,s[j]);
                    if(const P* pp=object_cast<P>(&o2)) {
                        ans = squared_distance(*pp,v->point());
                        if(ans>sum) sum=ans;
                    }
                }
            }
        }
    }
    cout << setiosflags(ios::fixed) << setprecision(0);
    cout << ceil_to_double(sqrt(to_double(sum))) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    while(cin >> n && n>0) {
        testcase();
    }
    return 0;
}

