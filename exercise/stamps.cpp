#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <cstring>
#include <CGAL/QP_functions.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#ifdef CGAL_USE_GMP 
#include <CGAL/Gmpzf.h> 
typedef CGAL::Gmpzf ET; 
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif


using namespace std;

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 SEG;

double mat[210][210];
int t;
P l[210];
P s[210];
SEG w[2010];
SEG S1;
int M[210];
int L,S,W;
P P1,P2;

void solve() {
    int X[210];

    for(int i=0;i<L;i++) {
        X[i] = i;
    }
    Program qp (CGAL::SMALLER, true, 1, true, 4096);
    for(int i=0;i<S;i++) {
        for(int j=0;j<L;j++) {
            if(mat[j][i]!=0) {
                qp.set_a(X[j],i,1.0/mat[j][i]);
                qp.set_a(X[j],i+S,-1.0/mat[j][i]);
            }
        }
        qp.set_b(i,M[i]);
        qp.set_b(i+S,-1);
    }
    Solution sol = CGAL::solve_linear_program(qp, ET());
    assert (sol.solves_linear_program(qp));
    if(sol.is_optimal()) {
        cout << "yes" << endl;
    }
    else cout << "no" << endl;
}

int main() {
    bool flag;
    int x,y,a,b,c,d;

    cin >> t;
    while(t--) {
        cin >> L >> S >> W;
        for(int i=0;i<L;i++) {
            cin >> x >> y;
            l[i] = P(x,y);
        }
        for(int i=0;i<S;i++) {
            cin >> x >> y >> M[i];
            s[i] = P(x,y);
        }
        for(int i=0;i<W;i++) {
            cin >> a >> b >> c >> d;
            P1 = P(a,b);
            P2 = P(c,d);
            w[i] = SEG(P1,P2);
        }
        memset(mat,0,sizeof(mat));
        for(int i=0;i<L;i++)
            for(int j=0;j<S;j++) {
                S1 = SEG(l[i],s[j]);
                flag = 1;
                for(int k=0;k<W;k++)
                    if(do_intersect(S1,w[k])) {
                        flag = 0;
                        break;
                    }
                if(flag) mat[i][j]=CGAL::to_double(squared_distance(l[i],s[j]));
            }
        solve();
    }
    return 0;
}

