#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_iterator  Face_iterator;

Triangulation::Vertex_handle v, s;
Triangulation::Face_handle f;
K::FT sum;

inline int minh(int x, int y)
{
    if(x>y) return y; else return x;
}

double ans;
double tmp;
map<K::Point_2,int> mmap;

int main()
{
    // read number of points
    ios::sync_with_stdio(false);
    int n, m;
    int x,y;
    vector<K::Point_2> pts;
    pts.reserve(110010);
    K::Point_2 p;
    int L,B,R,T;
    double time[110010];
    int t1 ,t2;

    while(cin >> n && n > 0)
    {
        // read points
        Triangulation t;
        pts.clear();
        mmap.clear();
        cin >> L >> B >> R >> T;
        memset(time,0,sizeof(time));
        for (int i = 0; i < n; ++i) 
        {
            cin >> x >> y;
            K::Point_2 p(x,y);
            pts.push_back(p);
            //t.insert(p);
            mmap.insert(pair<K::Point_2,int>(p,i));
            time[i]=1.0 * minh(minh(x-L,R-x),minh(y-B,T-y))-0.5;
            if(time[i]<0) time[i]=0;
        }
        t.insert(pts.begin(),pts.end());
        for(Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end();++e)
        {
            sum = squared_distance(t.segment(e).source(),t.segment(e).target());
            tmp = (sqrt(to_double(sum))-1)/2;
            if(tmp<0) tmp=0;
            t1 = mmap.find(t.segment(e).source())->second;
            if(tmp<time[t1]) time[t1]=tmp;
            t2 = mmap.find(t.segment(e).target())->second;
            if(tmp<time[t2]) time[t2]=tmp;
        }
        sort(time,time+n);
        cout << setiosflags(ios::fixed);
        cout << setprecision(0);
        cout << ceil(sqrt(time[0])) << " " << ceil(sqrt(time[n/2])) << " " << ceil(sqrt(time[n-1]))<<endl;
    }
    return 0;
}

