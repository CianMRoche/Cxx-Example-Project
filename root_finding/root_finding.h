#ifndef ROOT_FINDING
#define ROOT_FINDING

double bisection(std::function<double(double)> func, double left_limit, double right_limit, double tol, int max_iter);

double newton_raphson(std::function<double(double)> func, std::function<double(double)> derivative, double x, double tol, int max_iter);

double secant(std::function<double(double)> func, double x0, double x1, double tol, int max_iter);

#endif // ROOT_FINDING