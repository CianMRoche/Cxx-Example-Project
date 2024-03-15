# include <cmath>
# include "function_input.h"

// Function to find the root of
double f(double x) {
  return x*x - 2;
}

// Derivative of the function (only necessary for Newton-Raphson method)
double df(double x) {
  return 2*x;
}