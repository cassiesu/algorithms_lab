#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

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

int p, a, b;
Solution s;
int flag;
double ans;

int main() 
{
    const int X = 0;
    const int Y = 1;
    const int Z = 2;

    while( cin >> p >> a >> b && p > 0)
    {
        if(p==1)
        {
            Program lp (CGAL::SMALLER, true, 0, false, 0); 
            lp.set_a(X, 0, 1);
            lp.set_a(Y, 0, 1);
            lp.set_b(0, 4);
            lp.set_a(X, 1, 4);
            lp.set_a(Y, 1, 2);
            lp.set_b(1, a * b);
            lp.set_a(X, 2, -1);
            lp.set_a(Y, 2, 1);
            lp.set_b(2, 1);
            lp.set_d(X, X, 2*a);
            lp.set_c(Y, - b);
            s = CGAL::solve_quadratic_program(lp, ET());
            assert (s.solves_quadratic_program(lp));
            flag = -1;
        }
        else
        {
            Program lp (CGAL::SMALLER, false, 0, true, 0); 
            lp.set_a(X, 0, -1);
            lp.set_a(Y, 0, -1);
            lp.set_b(0, 4);
            lp.set_a(X, 1, -4);
            lp.set_a(Y, 1, -2);
            lp.set_a(Z, 1, 1);
            lp.set_b(1, a * b);
            lp.set_a(X, 2, 1);
            lp.set_a(Y, 2, -1);
            lp.set_b(2, 1);
            /*
            lp.set_a(X, 3, 1);
            lp.set_b(3, 0);
            lp.set_a(Y, 4, 1);
            lp.set_b(4, 0);
            */
            lp.set_d(X, X, 2*a);
            lp.set_c(Y, b);
            lp.set_d(Z, Z, 2);
            /*lp.set_u(X, true, 0);
            lp.set_u(Y, true, 0);
            lp.set_u(Z, true, 0);
            */
            s = CGAL::solve_quadratic_program(lp, ET());
            assert (s.solves_quadratic_program(lp));
            flag = 1;
        }
        if(s.is_optimal())
        {
            cout << setiosflags(ios::fixed);
            cout << setprecision(0);
            ans = flag * ceil(to_double(s.objective_value()));
            //if(ans>-0.0001 && ans < 0.0001) cout << 0 << endl; else 
            cout << ans << endl;
        }
        else
        {
            if(s.is_unbounded())
                cout << "unbounded" << endl;
            else
                cout << "no" << endl;
        }
/*
        if (s.is_optimal() && (s.objective_value() < 0)) 
        {
            // *opt := x, *(opt+1) := y, *(opt+2) := gamma
            CGAL::Quadratic_program_solution<ET>::Variable_value_iterator 
                opt = s.variable_values_begin(); 
            CGAL::Quotient<ET> x = *opt;
            CGAL::Quotient<ET> y = *(opt+1);
            CGAL::Quotient<ET> gamma = *(opt+2);
            std::cout << "There is a valid exposure:\n";
            std::cout << " Center = ("        // (x/2, y/2)
                << x/2 << ", " <<  y/2 
                << ")\n"; 
            std::cout << " Squared Radius = " // gamma + x^2/4 + y^2/4
                << gamma + x*x/4 + y*y/4 << "\n";
        } 
        else
            std::cout << "There is no valid exposure.";
        std::cout << "\n";
*/
    }
    return 0;
}
