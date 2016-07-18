#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::Line_2 L;

struct node {
    int x;
    int y;
    node() {}
    node(const int &a, const int &b) {
        x = a;
        y = b;
    }
};

inline bool operator<(const node &a, const node &b) {
    return a.y > b.y;
}

P hp[8010];
R r1,r2,r3,r4;
P p[8010][7];
P tp;
int tt, maxh;
node tn;
int ans;
queue<int> q[8010];
priority_queue<node> qu;

inline bool check(P p1, P p2, P p3) {
    return left_turn(p1,p2,p3);
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, a,b;
    int x,y;
    int c;

    cin >> c;
    while(c--) {
        cin >> m >> n;
        for(int i=0;i<m;i++) {
            cin >> x >> y;
            hp[i] = P(x,y);
            while(!q[i].empty()) q[i].pop();
        }
        for(int i=0;i<n;i++) {
            cin >> x >> y >> a >> b;
            p[i][0] = P(x,y);
            p[i][1] = P(a,b);
            cin >> x >> y >> a >> b;
            p[i][2] = P(x,y);
            p[i][3] = P(a,b);
            cin >> x >> y >> a >> b;
            p[i][4] = P(x,y);
            p[i][5] = P(a,b);
            if(check(p[i][0],p[i][1],p[i][2])) 
                swap(p[i][0],p[i][1]);
            if(check(p[i][2],p[i][3],p[i][1]))
                swap(p[i][2],p[i][3]);
            if(check(p[i][5],p[i][4],p[i][3]))
                swap(p[i][5],p[i][4]);
            for(int j=0;j<m-1;j ++) {
                if((check(p[i][0],p[i][1],hp[j]) || check(p[i][2],p[i][3],hp[j]) || check(p[i][5],p[i][4],hp[j])) 
                    || (check(p[i][0],p[i][1],hp[j+1]) || check(p[i][2],p[i][3],hp[j+1]) || check(p[i][5],p[i][4],hp[j+1])))
                    continue;
                q[j].push(i);
            }
        }
        tt=maxh=0;
        ans = 10000;
        while(!qu.empty()) qu.pop();
        for(int i=0;i<m-1;i++) {
            if(q[i].empty()) break;
            tt = q[i].front();
            if(tt>maxh) maxh = tt;
            q[i].pop();
            qu.push(node(i,tt));
        }
        while(1) {
            tn = qu.top();
            if(maxh-tn.y<ans) ans = maxh-tn.y;
            qu.pop();
            if(q[tn.x].empty()) break;
            tt = q[tn.x].front();
            if(tt>maxh) maxh = tt;
            qu.push(node(tn.x,tt));
            q[tn.x].pop();
        }
        cout << ans + 1 << endl;
    }
    return 0;
}
