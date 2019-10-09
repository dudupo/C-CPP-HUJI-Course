#include "infi.h"


double derivative(RealFunction function, double position, double eps) {
  return (double)(function(position + eps) - function(position - eps))/(2*eps);
}
double integration(RealFunction function, double start,
   double end, unsigned int parts){
     double sum = 0, eps = (double)(end - start)/parts;
     for ( int i = 0; i < parts; i++) {
        sum += function( start + eps*i ) * eps;
     }
     return sum;
}
