#include <cmath>
#include <functional>
#include "root_finding.h"

// Bisection method
/*
* The bisection method in mathematics is a root-finding method that repeatedly bisects an interval and then selects a subinterval in which a root must lie for further processing.
* The method is also called the interval halving method, the binary search method, or the dichotomy method.
* The bisection method is a simple and robust method, but it is also relatively slow.
*
* Parameters
* ----------
* func : function
*    The function for which we are trying to find the root.
* left_limit : float
*   The left limit of the interval.
* right_limit : float
*  The right limit of the interval.
* tol : float
*  The tolerance for the root.
* max_iter : int
* The maximum number of iterations.
*
* Returns
* -------
* float
* The root of the function.
*/
double bisection(std::function<double(double)> func, double left_limit, double right_limit, double tol, int max_iter) {
    double f_left = func(left_limit);
    double f_right = func(right_limit);
    if (f_left * f_right > 0) {
        throw std::runtime_error("Root not bracketed, adjust left and right limits.");
    }

    // Bisection loop
    for (int i = 0; i < max_iter; i++) {
        double mid = (left_limit + right_limit) / 2;
        double f_mid = func(mid);
        if (f_mid == 0 || (right_limit - left_limit) / 2 < tol) {
            return mid;
        }
        if (f_mid * f_left < 0) {
            right_limit = mid;
            f_right = f_mid;
        } else {
            left_limit = mid;
            f_left = f_mid;
        }
    }
    
    return (left_limit + right_limit) / 2;
}

// Newton-Raphson method, where both f and df are passed as function
/*
* The Newton-Raphson method is a root-finding algorithm that uses the first few terms of the Taylor series of a function f in the vicinity of a suspected root.
* The method is named after Isaac Newton and Joseph Raphson, who first published it.
* The Newton-Raphson method is defined by the recurrence relation
* x_{n+1} = x_n - f(x_n) / f'(x_n)
* where x_n is the current approximation to the root, f(x_n) is the value of the function at x_n, and f'(x_n) is the derivative of the function at x_n.
* The method has a convergence rate which is faster than that of the bisection method, but it requires the computation of derivatives.
*
* Parameters
* ----------
* func : function
*    The function for which we are trying to find the root.
* derivative : function
*    The derivative of the function.
* x : float
*   The initial guess for the root.
* tol : float
*  The tolerance for the root.
* max_iter : int
* The maximum number of iterations.
*
* Returns
* -------
* float
* The root of the function.
*/
double newton_raphson(std::function<double(double)> func, std::function<double(double)> derivative, double x, double tol, int max_iter) {
    for (int i = 0; i < max_iter; i++) {
        double dx = -func(x) / derivative(x);
        x += dx;
        if (std::abs(dx) < tol) {
        return x;
        }
    }
    return x;
}

// Secant method
double secant(std::function<double(double)> func, double x0, double x1, double tol, int max_iter) {
    /*
    * The secant method is a root-finding algorithm that uses a succession of roots of secant lines to better approximate a root of a function f.
    * The secant method can be thought of as a finite-difference approximation of Newton's method. 
    * The method has a convergence rate which is slower than that of the latter method, but does not require the computation of derivatives.
    * The secant method is defined by the recurrence relation 
    * x_{n+1} = x_n - f(x_n) * (x_n - x_{n-1}) / (f(x_n) - f(x_{n-1}))
    * where x_n and x_{n-1} are the current and previous approximations to the root, respectively.
    * The method is not guaranteed to converge, but under suitable conditions it is known to converge superlinearly, and therefore faster than the bisection method.
    * 
    * Parameters
    * ----------
    * func : function
    *    The function for which we are trying to find the root.
    * x0 : float
    *   The initial guess for the root.
    * x1 : float
    *  The second initial guess for the root.
    * tol : float
    *  The tolerance for the root.
    * max_iter : int
    * The maximum number of iterations.
    * 
    * Returns
    * -------
    * float
    * The root of the function.
    */
    for (int i = 0; i < max_iter; i++) {
        double dx = (x1 - x0) * func(x1) / (func(x1) - func(x0));
        x0 = x1;
        x1 -= dx;
        if (std::abs(dx) < tol) {
            return x1;
        }
    }
    return x1;
}