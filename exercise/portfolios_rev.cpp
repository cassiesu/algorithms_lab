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

int X[50];
int cost[50], ret[50];
int v[50][50];
int C, V; 
int n, m;

bool solve(int R) {
    double ans;
    Program qp (CGAL::SMALLER, true, 0, false, 0); 
    for(int i=1;i<=n;i++) {
        qp.set_a(X[i],0,cost[i]);
        qp.set_a(X[i],1,-ret[i]);
    }
    qp.set_b(0,C);
    qp.set_b(1,-R);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            qp.set_d(X[i],X[j], 2 * v[i][j]);
        }
    qp.set_c0(-V);
    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert (s.solves_quadratic_program(qp));
    if(s.is_optimal()) {
        ans = to_double(s.objective_value());
        if(ans <= 0) {
            return 1;
        }
    }
    return 0;
}

int search(int left, int right) {
    if(right-left<=1)
    {
        if(solve(right)) return right;
        else return left;
    }
    int mid = (left + right) / 2;
    if(solve(mid)) 
    {
        return search(mid,right); 
    }
    else return search(left,mid-1);
}

int main() {

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
            cin >> C >> V;
            cout << search(0,100000000) << endl;
        }
    }
    return 0;
}

