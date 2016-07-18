// example: find the risk-optimal investment strategy
// in Swatch and Credit Suisse shares (data as in lecture)
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

using namespace std;

// choose exact floating-point type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET; 
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
    int X[110];
    int cost[110], ret[110];
    int v[110][110];
    int C, R, V; 
    int n, m;
    double ans;

    while( cin >> n >> m && n + m > 0)
    {
        for(int i=1;i<=n;i++)
        {
            X[i] = i-1;
            cin >> cost[i] >> ret[i];
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                cin >> v[i][j];
        for(int t=1;t<=m;t++)
        {
            cin >> C >> R >> V;
            Program qp (CGAL::SMALLER, true, 0, false, 0); 
            for(int i=1;i<=n;i++)
            {
                qp.set_a(X[i],0,cost[i]);
                qp.set_a(X[i],1,-ret[i]);
            }
            qp.set_b(0,C);
            qp.set_b(1,-R);
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                {
                    qp.set_d(X[i],X[j], 2 * v[i][j]);
                }
            qp.set_c0(-V);
            Solution s = CGAL::solve_quadratic_program(qp, ET());
            assert (s.solves_quadratic_program(qp));
            if(s.is_optimal())
            {
                ans = to_double(s.objective_value());
                if(ans <= 0)
                    cout << "Yes." << endl;
                else
                    cout << "No." << endl;
            }
            else
                cout << "No." << endl;
        }
    }
    return 0;
}

