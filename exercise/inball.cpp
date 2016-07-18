#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <cmath>

using namespace std;

// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

Solution s;
int n,m;
double ans;
double sum;

int main() 
{
    int n,d;
    int X[20];
    double ans;
    int tmp;
    int sum;
    int summit;

    while( cin >> n && n > 0)
    {
        cin >> d;
        for(int i=0;i<=d;i++)
            X[i]=i;
        Program lp(CGAL::SMALLER, false, 0, false, 0); 
        for(int i=0;i<n;i++)
        {
            sum = 0;
            for(int j=0;j<d;j++)
            {
                cin >> tmp;
                lp.set_a(X[j],i,tmp);
                sum+=tmp*tmp;
            }
            cin >> tmp;
            lp.set_b(i,tmp);
            lp.set_a(X[d],i,sqrt(sum)); 
        }
        lp.set_c(X[d],-1); 
        s = CGAL::solve_linear_program(lp, ET());
        assert (s.solves_linear_program(lp));
        if(s.is_optimal())
        {
            cout << setiosflags(ios::fixed);
            cout << setprecision(0);
            if(s.objective_value()<=0) 
                cout << floor(to_double(-s.objective_value()))<<endl;
            else
                cout << "none" << endl;
        }
        else
        {
            if(s.is_unbounded())
                cout << "inf" << endl;
            else
                cout << "none" << endl;
        }
    }
    return 0;
}

